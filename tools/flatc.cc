/*
Copyright 2017 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "flatbuffers/flatc.h"
#include <iostream>
#include <string>
#include "flatbuffers/code_generators.h"
// Generates Lullaby-specific classes from flatbuffer schemas.
//
// The default native code generated by flatbuffers is less than ideal for use
// by Lullaby.  Instead, we introduce our own code generator for generating
// native types (similar to the code generated by flatc when using the
// --gen-obj-api flag).  This code has some special behaviour that makes it
// easier to work with in the context of Lullaby.  Some key highlights include:
//
// * All classes are registered with Lullaby's TypeId system.
// * Any schema type marked with "native_type" is automatically mapped into a
//   custom C++ class.  (eg. the lull::Vec2 table maps to mathfu::vec2).
// * All nested types (tables and structs) are "inlined" by default: they are
//   direct members and not pointers to objects.  This simplifies the memory
//   and ownership model for data members.
// * Union types are proper unions in that the memory for the object is entirely
//   "inline" as well, whereas the default flatc unions are dynamically
//   allocated which leads to confusing memory and ownership semantics.
// * The "defaults_to_null" attribute can be used to make specific members use
//   lull::Optional.  This allows us to selectively provide pointer-like
//   behaviour for specific members, without introducing the memory and
//   ownership issues you get when dealing with dynamic data.
// * The "dynamic" attribute can be used to make a specific field use
//   std::unique_ptr.  This is useful for supporting cyclical data dependencies
//   (eg. Table X has a field of table X) and is the same as the default
//   flatbuffer gen-object-api support.
class CodeGenerator : public flatbuffers::BaseGenerator {
 public:
  CodeGenerator(const flatbuffers::Parser& parser, const std::string& path,
                const std::string& file_name)
      : flatbuffers::BaseGenerator(parser, path, file_name, "", "::") {
    curr_namespace_ = &root_namespace_;
  }

  bool generate() override;

 private:
  void GenerateStructMember(const flatbuffers::FieldDef& field);

  void SetNameSpace(const flatbuffers::Namespace* ns);
  std::string NativeName(const std::string& name) const;
  std::string NativeFullName(const flatbuffers::Definition& def) const;
  std::string GetType(const flatbuffers::Type& type,
                      const flatbuffers::FieldDef* field) const;
  std::string GetDefaultValue(const flatbuffers::FieldDef& field) const;

  void GenerateInclude(const std::string& fullname);

  void GenerateFwdDecl(const flatbuffers::Definition& def);

  void GenerateEnumDecl(const flatbuffers::EnumDef& def);
  void GenerateStructDecl(const flatbuffers::StructDef& def);
  void GenerateEnumFunctions(const flatbuffers::EnumDef& def);
  void GenerateStructFunctions(const flatbuffers::StructDef& def);
  void GenerateRegisterTypeId(const flatbuffers::Definition& def);
  void GenerateMemberSerialize(const flatbuffers::FieldDef& field);

  flatbuffers::CodeWriter code_;
  flatbuffers::Namespace root_namespace_;
  const flatbuffers::Namespace* curr_namespace_ = nullptr;
};

// Adds or removes scopes so that the code is generated in the provided
// namespace.  This is done by finding a common "root" between the current
// namespace and requested namespace, closing scope until the root, and
// opening new scopes following the path of the requested namespace.
void CodeGenerator::SetNameSpace(const flatbuffers::Namespace* ns) {
  const auto& current = curr_namespace_->components;
  const auto& target = ns->components;

  size_t count = 0;
  while (count < current.size() && count < target.size()) {
    if (current[count] != target[count]) {
      break;
    }
    ++count;
  }
  for (size_t i = current.size(); i > count; --i) {
    code_ += "}  // namespace " + current[i - 1];
  }
  for (size_t i = count; i < target.size(); ++i) {
    code_ += "namespace " + target[i] + " {";
  }
  curr_namespace_ = ns;
}

// Gets a pointer to the attribute value for a given definition, or nullptr if
// no such attribute exists.
const std::string* GetAttribute(const flatbuffers::Definition& def,
                                const char* name) {
  const auto* attribute = def.attributes.Lookup(name);
  if (attribute) {
    return &attribute->constant;
  } else {
    return nullptr;
  }
}

// Gets the default value for a given field.
std::string CodeGenerator::GetDefaultValue(
    const flatbuffers::FieldDef& field) const {
  const flatbuffers::Type& type = field.value.type;
  std::string value = field.value.constant;

  // For enum types, we want to use the enum identifier for the default value,
  // not the underlying integral value.
  if (type.enum_def && IsScalar(type.base_type)) {
    flatbuffers::EnumDef& enum_def = *type.enum_def;
    const int int_value = std::stoi(value);
    auto* enum_value = enum_def.ReverseLookup(int_value, false);
    if (enum_value) {
      const std::string full_name = enum_def.name + "_" + enum_value->name;
      return WrapInNameSpace(enum_def.defined_namespace, full_name);
    } else if (enum_def.attributes.Lookup("bit_flags") != nullptr &&
               int_value == 0) {
      const std::string full_name = enum_def.name + "_NONE";
      return WrapInNameSpace(enum_def.defined_namespace, full_name);
    }
  }

  // If the field has a native_default value, just use it directly.
  const auto* native_default = GetAttribute(field, "native_default");
  if (native_default) {
    return *native_default;
  }

  // For floating-point types, append the 'f' at the end of the default value.
  if (type.base_type == flatbuffers::BASE_TYPE_FLOAT) {
    if (value.back() != 'f') {
      value.push_back('f');
    }
  }
  return value;
}

// Generates the class name for the "native" implementation for a given
// flatbuffer type.  This follows the same convention established by the
// default flatbuffer native code generator and simply appends "T" to the
// given name.
std::string CodeGenerator::NativeName(const std::string& name) const {
  return name + "T";
}

std::string CodeGenerator::NativeFullName(
    const flatbuffers::Definition& def) const {
  return NativeName(WrapInNameSpace(def));
}

std::string GetBasicType(const flatbuffers::BaseType& base_type) {
  switch (base_type) {
    case flatbuffers::BASE_TYPE_NONE:
      return "";
    case flatbuffers::BASE_TYPE_UTYPE:
      return "uint8_t";
    case flatbuffers::BASE_TYPE_BOOL:
      return "bool";
    case flatbuffers::BASE_TYPE_CHAR:
      return "int8_t";
    case flatbuffers::BASE_TYPE_UCHAR:
      return "uint8_t";
    case flatbuffers::BASE_TYPE_SHORT:
      return "int16_t";
    case flatbuffers::BASE_TYPE_USHORT:
      return "uint16_t";
    case flatbuffers::BASE_TYPE_INT:
      return "int32_t";
    case flatbuffers::BASE_TYPE_UINT:
      return "uint32_t";
    case flatbuffers::BASE_TYPE_LONG:
      return "int64_t";
    case flatbuffers::BASE_TYPE_ULONG:
      return "uint64_t";
    case flatbuffers::BASE_TYPE_FLOAT:
      return "float";
    case flatbuffers::BASE_TYPE_DOUBLE:
      return "double";
    case flatbuffers::BASE_TYPE_STRING:
      return "std::string";
    default:
      return "";
  }
}

// Returns the native C++ type for a given flatbuffer type.
std::string CodeGenerator::GetType(const flatbuffers::Type& type,
                                   const flatbuffers::FieldDef* field) const {
  if (type.enum_def && IsScalar(type.base_type)) {
    return WrapInNameSpace(*type.enum_def);
  }

  switch (type.base_type) {
    case flatbuffers::BASE_TYPE_NONE:
    case flatbuffers::BASE_TYPE_UTYPE:
    case flatbuffers::BASE_TYPE_BOOL:
    case flatbuffers::BASE_TYPE_CHAR:
    case flatbuffers::BASE_TYPE_UCHAR:
    case flatbuffers::BASE_TYPE_SHORT:
    case flatbuffers::BASE_TYPE_USHORT:
    case flatbuffers::BASE_TYPE_INT:
    case flatbuffers::BASE_TYPE_LONG:
    case flatbuffers::BASE_TYPE_ULONG:
    case flatbuffers::BASE_TYPE_FLOAT:
    case flatbuffers::BASE_TYPE_DOUBLE:
    case flatbuffers::BASE_TYPE_STRING:
      return GetBasicType(type.base_type);
    case flatbuffers::BASE_TYPE_UINT: {
      const auto* hashvalue = GetAttribute(*field, "hashvalue");
      return hashvalue ? "lull::HashValue" : GetBasicType(type.base_type);
    }
    case flatbuffers::BASE_TYPE_VECTOR: {
      const std::string name = GetType(type.VectorType(), field);
      return "std::vector<" + name + ">";
    }
    case flatbuffers::BASE_TYPE_STRUCT: {
      const auto def = field->value.type.struct_def;
      const auto* native_type = GetAttribute(*def, "native_type");
      const std::string name =
          native_type ? *native_type : NativeFullName(*def);

      const auto* nullable = GetAttribute(*field, "defaults_to_null");
      if (nullable) {
        return "lull::Optional<" + name + ">";
      }

      const auto* dynamic = GetAttribute(*field, "dynamic");
      if (dynamic) {
        return "std::shared_ptr<" + name + ">";
      }

      return name;
    }
    case flatbuffers::BASE_TYPE_UNION: {
      const auto def = field->value.type.enum_def;
      const auto* native_type = GetAttribute(*def, "native_type");
      if (native_type) {
        return *native_type;
      } else {
        return NativeFullName(*def);
      }
    }
    default:
      return "";
  }
}

// Generates the declaration for a native StructDef class.
void CodeGenerator::GenerateStructMember(const flatbuffers::FieldDef& field) {
  if (field.deprecated) {
    return;
  }

  code_.SetValue("FIELD_TYPE", GetType(field.value.type, &field));
  code_.SetValue("FIELD_NAME", field.name);
  code_.SetValue("FIELD_DEFAULT", GetDefaultValue(field));

  switch (field.value.type.base_type) {
    case flatbuffers::BASE_TYPE_NONE:
      break;
    case flatbuffers::BASE_TYPE_UTYPE:
      break;
    case flatbuffers::BASE_TYPE_BOOL:
    case flatbuffers::BASE_TYPE_CHAR:
    case flatbuffers::BASE_TYPE_UCHAR:
    case flatbuffers::BASE_TYPE_SHORT:
    case flatbuffers::BASE_TYPE_USHORT:
    case flatbuffers::BASE_TYPE_INT:
    case flatbuffers::BASE_TYPE_UINT:
    case flatbuffers::BASE_TYPE_LONG:
    case flatbuffers::BASE_TYPE_ULONG:
    case flatbuffers::BASE_TYPE_FLOAT:
    case flatbuffers::BASE_TYPE_DOUBLE:
      code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}} = {{FIELD_DEFAULT}};";
      break;
    case flatbuffers::BASE_TYPE_STRING:
      code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}};";
      break;
    case flatbuffers::BASE_TYPE_VECTOR: {
      code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}};";
      break;
    }
    case flatbuffers::BASE_TYPE_STRUCT: {
      const flatbuffers::StructDef& def = *field.value.type.struct_def;
      const auto* native_default = GetAttribute(field, "native_default");
      if (native_default == nullptr) {
        native_default = GetAttribute(def, "native_default");
      }

      const bool nullable = GetAttribute(field, "defaults_to_null") ||
                            GetAttribute(field, "dynamic");
      if (native_default && !nullable) {
        code_.SetValue("FIELD_DEFAULT", *native_default);
        code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}} = {{FIELD_DEFAULT}};";
      } else {
        code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}};";
      }
      break;
    }
    case flatbuffers::BASE_TYPE_UNION: {
      code_ += "  {{FIELD_TYPE}} {{FIELD_NAME}};";
      break;
    }
  }
}

// Generates the forward declaration for the given flatbuffer type.
void CodeGenerator::GenerateFwdDecl(const flatbuffers::Definition& def) {
  code_.SetValue("DEF_NAME", NativeName(def.name));
  code_ += "class {{DEF_NAME}};";
}

// Generates the entire class declaration for a given flatbuffer StructDef.
void CodeGenerator::GenerateStructDecl(const flatbuffers::StructDef& def) {
  code_.SetValue("FB_TYPE", def.name);
  code_.SetValue("DEF_NAME", NativeName(def.name));

  code_ += "class {{DEF_NAME}} {";
  code_ += " public:";
  code_ += "  using FlatBufferType = {{FB_TYPE}};";
  code_ += "";
  code_ += "  {{DEF_NAME}}() {}";
  code_ += "";
  for (const auto& field : def.fields.vec) {
    GenerateStructMember(*field);
  }
  code_ += "";
  code_ += "  template <typename Archive>";
  code_ += "  void SerializeFlatbuffer(Archive archive);";
  code_ += "};";
  code_ += "";
}

// Generates the entire class declaration for a given flatbuffer EnumDef.
void CodeGenerator::GenerateEnumDecl(const flatbuffers::EnumDef& def) {
  code_.SetValue("FB_TYPE", def.name);
  code_.SetValue("DEF_NAME", NativeName(def.name));
  code_.SetValue("ENUM_BASE", GetBasicType(def.underlying_type.base_type));

  code_ += "class {{DEF_NAME}} {";
  code_ += " public:";
  code_ += "  using FlatBufferType = {{FB_TYPE}};";
  code_ += "  static const {{ENUM_BASE}} kNone = {{FB_TYPE}}_NONE;";
  code_ += "";
  code_ += "  {{DEF_NAME}}() {}";
  code_ += "  ~{{DEF_NAME}}() { reset(); }";
  code_ += "";
  code_ += "  {{DEF_NAME}}(const {{DEF_NAME}}& rhs) { assign(rhs); }";
  code_ += "  {{DEF_NAME}}& operator=(const {{DEF_NAME}}& rhs) {";
  code_ += "    assign(rhs);";
  code_ += "    return *this;";
  code_ += "  }";
  code_ += "";
  code_ += "  void reset();";
  code_ += "";
  code_ += "  FlatBufferType type() const {";
  code_ += "    return type_;";
  code_ += "  }";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  T* get() {";
  code_ += "    return type_ == get_type<T>() ?";
  code_ += "        reinterpret_cast<T*>(&data_) : nullptr;";
  code_ += "  }";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  const T* get() const {";
  code_ += "    return type_ == get_type<T>() ?";
  code_ += "        reinterpret_cast<const T*>(&data_) : nullptr;";
  code_ += "  }";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  T* set();";
  code_ += "";
  code_ += "  template <typename Archive>";
  code_ += "  void SerializeFlatbuffer(FlatBufferType type, Archive archive);";
  code_ += "";
  code_ += " private:";
  code_ += "  void assign(const {{DEF_NAME}}& rhs);";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  void destroy() {";
  code_ += "    reinterpret_cast<T*>(&data_)->~T();";
  code_ += "  }";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  static FlatBufferType get_type() {";
  code_ += "    return {{FB_TYPE}}_NONE;";
  code_ += "  }";
  code_ += "";
  code_ += "  template <typename T>";
  code_ += "  using Store = std::aligned_storage<sizeof(T), alignof(T)>;";
  code_ += "  union Buffer {";
  for (const auto& value : def.vals.vec) {
    if (value->name != "NONE") {
      code_.SetValue("KEY_TYPE", NativeFullName(*value->union_type.struct_def));
      code_.SetValue("KEY", value->name);
      code_ += "    Store<{{KEY_TYPE}}>::type {{KEY}}_;";
    }
  }
  code_ += "  };";
  code_ += "  Buffer data_;";
  code_ += "  FlatBufferType type_ = {{FB_TYPE}}_NONE;";
  code_ += "};";
  code_ += "";
}

// Generates the function implementations for the get_type(), set(), reset()
// and Serialize() functions for EnumDef types.
void CodeGenerator::GenerateEnumFunctions(const flatbuffers::EnumDef& def) {
  code_.SetValue("FB_TYPE", def.name);
  code_.SetValue("DEF_NAME", NativeName(def.name));
  code_ += "inline void {{DEF_NAME}}::reset() {";
  code_ += "  switch (type_) {";
  for (const auto& value : def.vals.vec) {
    if (value->name != "NONE") {
      code_.SetValue("KEY_TYPE", NativeFullName(*value->union_type.struct_def));
      code_.SetValue("KEY", value->name);
      code_ += "    case {{FB_TYPE}}_{{KEY}}: {";
      code_ += "      destroy<{{KEY_TYPE}}>();";
      code_ += "      break;";
      code_ += "    }";
    }
  }
  code_ += "    default:";
  code_ += "      break;";
  code_ += "  }";
  code_ += "  type_ = {{FB_TYPE}}_NONE;";
  code_ += "}";
  code_ += "";
  code_ += "inline void {{DEF_NAME}}::assign(const {{DEF_NAME}}& rhs) {";
  code_ += "  reset();";
  code_ += "  switch (rhs.type_) {";
  for (const auto& value : def.vals.vec) {
    if (value->name != "NONE") {
      code_.SetValue("KEY_TYPE", NativeFullName(*value->union_type.struct_def));
      code_.SetValue("KEY", value->name);
      code_ += "    case {{FB_TYPE}}_{{KEY}}: {";
      code_ += "      *set<{{KEY_TYPE}}>() = *rhs.get<{{KEY_TYPE}}>();";
      code_ += "      break;";
      code_ += "    }";
    }
  }
  code_ += "    default:";
  code_ += "      break;";
  code_ += "  }";
  code_ += "}";
  code_ += "";
  code_ += "template <typename T>";
  code_ += "T* {{DEF_NAME}}::set() {";
  code_ += "  reset();";
  code_ += "  type_ = get_type<T>();";
  code_ += "  if (type_ != kNone) {";
  code_ += "    return new (&data_) T();";
  code_ += "  }";
  code_ += "  return nullptr;";
  code_ += "}";
  code_ += "";
  for (const auto& value : def.vals.vec) {
    if (value->name != "NONE") {
      code_.SetValue("KEY_TYPE", NativeFullName(*value->union_type.struct_def));
      code_.SetValue("KEY", value->name);
      code_ += "template <>";
      code_ += "inline {{FB_TYPE}} {{DEF_NAME}}::get_type<{{KEY_TYPE}}>() {";
      code_ += "  return {{FB_TYPE}}_{{KEY}};";
      code_ += "}";
      code_ += "";
    }
  }
  code_ += "";
  code_ += "template <typename Archive>";
  code_ += "void {{DEF_NAME}}::SerializeFlatbuffer(FlatBufferType type, Archive archive) {";
  code_ += "  switch (type) {";
  for (const auto& value : def.vals.vec) {
    if (value->name != "NONE") {
      code_.SetValue("KEY_TYPE", NativeFullName(*value->union_type.struct_def));
      code_.SetValue("KEY", value->name);
      code_ += "    case {{FB_TYPE}}_{{KEY}}: {";
      code_ += "      if (archive.IsDestructive()) {";
      code_ += "        set<{{KEY_TYPE}}>()->SerializeFlatbuffer(archive);";
      code_ += "      } else {";
      code_ += "        get<{{KEY_TYPE}}>()->SerializeFlatbuffer(archive);";
      code_ += "      }";
      code_ += "      break;";
      code_ += "    }";
    }
  }
  code_ += "    default:";
  code_ += "      if (archive.IsDestructive()) {";
  code_ += "        reset();";
  code_ += "      }";
  code_ += "      break;";
  code_ += "  }";
  code_ += "}";
  code_ += "";
}

bool IsDynamicField(const flatbuffers::FieldDef& field) {
  switch (field.value.type.base_type) {
    case flatbuffers::BASE_TYPE_NONE:
    case flatbuffers::BASE_TYPE_UTYPE:
    case flatbuffers::BASE_TYPE_BOOL:
    case flatbuffers::BASE_TYPE_CHAR:
    case flatbuffers::BASE_TYPE_UCHAR:
    case flatbuffers::BASE_TYPE_SHORT:
    case flatbuffers::BASE_TYPE_USHORT:
    case flatbuffers::BASE_TYPE_INT:
    case flatbuffers::BASE_TYPE_UINT:
    case flatbuffers::BASE_TYPE_LONG:
    case flatbuffers::BASE_TYPE_ULONG:
    case flatbuffers::BASE_TYPE_FLOAT:
    case flatbuffers::BASE_TYPE_DOUBLE:
      return false;
    case flatbuffers::BASE_TYPE_STRING:
    case flatbuffers::BASE_TYPE_VECTOR:
    case flatbuffers::BASE_TYPE_UNION:
      return true;
    case flatbuffers::BASE_TYPE_STRUCT:
      return field.value.type.struct_def->fixed == false;
    default: return false;
  }
}

// Generates the function implementations for the Serialize() functions for
// StructDef types.
void CodeGenerator::GenerateStructFunctions(const flatbuffers::StructDef& def) {
  code_.SetValue("DEF_NAME", NativeName(def.name));

  code_ += "template <typename Archive>";
  code_ += "void {{DEF_NAME}}::SerializeFlatbuffer(Archive archive) {";

  // Loop through the fields twice generating the appropriate serializer
  // function call.  The first time, only generate code for dynamic fields (eg.
  // tables, strings, vectors, and unions) and the second time generate the
  // rest.
  for (int i = 0; i < 2; ++i) {
    const bool process_dynamic_fields = (i == 0);
    for (const auto& field : def.fields.vec) {
      const auto& field_type = field->value.type.base_type;
      if (field->deprecated) {
        continue;
      } else if (field_type == flatbuffers::BASE_TYPE_NONE) {
        continue;
      } else if (field_type == flatbuffers::BASE_TYPE_UTYPE) {
        continue;
      } else if (IsDynamicField(*field) != process_dynamic_fields) {
        continue;
      } else {
        GenerateMemberSerialize(*field);
      }
    }
  }
  code_ += "}";
  code_ += "";
}

void CodeGenerator::GenerateMemberSerialize(
    const flatbuffers::FieldDef& field) {
  const flatbuffers::Type& type = field.value.type;
  code_.SetValue("FIELD_NAME", field.name);
  code_.SetValue("FIELD_OFFSET", std::to_string(field.value.offset));
  code_.SetValue("FIELD_DEFAULT", GetDefaultValue(field));
  code_.SetValue("FIELD_TYPE", GetType(type, &field));

  switch (type.base_type) {
    case flatbuffers::BASE_TYPE_NONE:
      // do nothing
      break;
    case flatbuffers::BASE_TYPE_UTYPE:
      // do nothing
      break;
    case flatbuffers::BASE_TYPE_BOOL:
    case flatbuffers::BASE_TYPE_CHAR:
    case flatbuffers::BASE_TYPE_UCHAR:
    case flatbuffers::BASE_TYPE_SHORT:
    case flatbuffers::BASE_TYPE_USHORT:
    case flatbuffers::BASE_TYPE_INT:
    case flatbuffers::BASE_TYPE_UINT:
    case flatbuffers::BASE_TYPE_LONG:
    case flatbuffers::BASE_TYPE_ULONG:
    case flatbuffers::BASE_TYPE_FLOAT:
    case flatbuffers::BASE_TYPE_DOUBLE: {
      if (type.enum_def) {
        // For enum types, the flatbuffer wire size and the C++ enum size may
        // not be the same.  So, we need to manually cast between the two for
        // serialization purposes.
        code_.SetValue("BASE_TYPE", GetBasicType(type.base_type));
        code_ += "  {{BASE_TYPE}} _{{FIELD_NAME}} = static_cast<{{BASE_TYPE}}>({{FIELD_NAME}});";
        code_ += "  archive.Scalar(&_{{FIELD_NAME}}, {{FIELD_OFFSET}}, {{FIELD_DEFAULT}});";
        code_ += "  {{FIELD_NAME}} = static_cast<{{FIELD_TYPE}}>(_{{FIELD_NAME}});";
      } else {
        code_ += "  archive.Scalar(&{{FIELD_NAME}}, {{FIELD_OFFSET}}, {{FIELD_DEFAULT}});";
      }
      break;
    }
    case flatbuffers::BASE_TYPE_STRING:
      code_ += "  archive.String(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
      break;
    case flatbuffers::BASE_TYPE_STRUCT: {
      const auto struct_def = type.struct_def;
      const auto* native_type = GetAttribute(*struct_def, "native_type");
      if (struct_def->fixed) {
        if (native_type) {
          code_ += "  archive.NativeStruct(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        } else {
          code_ += "  archive.Struct(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        }
      } else {
        if (native_type) {
          code_ += "  archive.NativeTable(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        } else {
          code_ += "  archive.Table(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        }
      }
      break;
    }
    case flatbuffers::BASE_TYPE_UNION: {
      code_ += "  archive.Union(&{{FIELD_NAME}}, {{FIELD_OFFSET}}, {{FIELD_TYPE}}::kNone);";
      break;
    }
    case flatbuffers::BASE_TYPE_VECTOR: {
      const flatbuffers::Type vector_type = type.VectorType();
      if (vector_type.base_type == flatbuffers::BASE_TYPE_STRUCT) {
        const auto struct_def = vector_type.struct_def;
        const auto native_type = struct_def->attributes.Lookup("native_type");
        if (struct_def->fixed) {
          if (native_type) {
            code_ += "  archive.VectorOfNativeStructs(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
          } else {
            code_ += "  archive.VectorOfStructs(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
          }
        } else {
          if (native_type) {
            code_ += "  archive.VectorOfNativeTables(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
          } else {
            code_ += "  archive.VectorOfTables(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
          }
        }
      } else if (vector_type.base_type == flatbuffers::BASE_TYPE_STRING) {
        code_ += "  archive.VectorOfStrings(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
      } else {
        if (vector_type.enum_def) {
          // For enum types, the flatbuffer wire size and the C++ enum size may
          // not be the same.  So, we have to be explicit about the types of
          // the vector data and the flatbuffer data when calling
          // VectorOfScalars.
          const flatbuffers::BaseType enum_type =
              vector_type.enum_def->underlying_type.base_type;
          code_.SetValue("BASE_TYPE", GetBasicType(enum_type));
          code_.SetValue("VECTOR_TYPE", GetType(vector_type, nullptr));
          code_ += "  archive.template VectorOfScalars<{{VECTOR_TYPE}}, {{BASE_TYPE}}>(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        } else {
          code_ += "  archive.VectorOfScalars(&{{FIELD_NAME}}, {{FIELD_OFFSET}});";
        }
      }
      break;
    }
  }
}

// Generates the LULLABY_SETUP_TYPEID call for the given type.
void CodeGenerator::GenerateRegisterTypeId(const flatbuffers::Definition& def) {
  code_.SetValue("TYPE_NAME", NativeFullName(def));
  code_ += "LULLABY_SETUP_TYPEID({{TYPE_NAME}});";
}

// Checks whether or not code should be generated for the given type.
bool ValidateType(const flatbuffers::Type& type) {
  if (type.struct_def) {
    const auto& def = *type.struct_def;
    const auto* native_type = GetAttribute(def, "native_type");
    if (native_type) {
      return false;
    }
    if (def.generated) {
      return false;
    }
    return true;
  } else if (type.enum_def) {
    const auto& def = *type.enum_def;
    if (!def.is_union) {
      return false;
    }
    if (def.generated) {
      return false;
    }
    return true;
  } else {
    return false;
  }
}

std::string GenerateIncludeGuard(std::string guard) {
  for (auto& c : guard) {
    c = toupper(c);
    if (!isalnum(c)) {
      c = '_';
    }
  }
  return "_" + guard + "_";
}

void CodeGenerator::GenerateInclude(const std::string& fullname) {
  const std::string basename =
      flatbuffers::StripPath(flatbuffers::StripExtension(fullname));
  if (basename != file_name_) {
    code_.SetValue("INCLUDE_FILE", basename + "_generated.h");
    code_ += "#include \"{{INCLUDE_FILE}}\"";
  }
}

bool CodeGenerator::generate() {
  std::vector<const flatbuffers::Type*> types;
  for (const auto& type_def : parser_.types_.vec) {
    if (ValidateType(*type_def)) {
      types.push_back(type_def);
    }
  }

  const std::string file_path = path_ + file_name_ + "_generated.h";
  code_.SetValue("INCLUDE_GUARD", GenerateIncludeGuard(file_path));

  code_ += "// Autogenerated code.  Do not edit.";
  code_ += "#ifndef {{INCLUDE_GUARD}}";
  code_ += "#define {{INCLUDE_GUARD}}";
  code_ += "";

  code_.SetValue("INCLUDE_FILE", "flatbuffers/" + file_name_ + "_generated.h");
  code_ += "#include <type_traits>";
  code_ += "#include <memory>";
  code_ += "#include \"{{INCLUDE_FILE}}\"";
  code_ += "#include \"lullaby/util/color.h\"";
  code_ += "#include \"lullaby/util/common_types.h\"";
  code_ += "#include \"lullaby/util/math.h\"";
  code_ += "#include \"lullaby/util/optional.h\"";
  code_ += "#include \"lullaby/util/typeid.h\"";
  for (auto& it : parser_.included_files_) {
    GenerateInclude(it.first);
  }
  code_ += "";

  for (auto type_def : types) {
    if (type_def->struct_def) {
      const flatbuffers::StructDef& def = *type_def->struct_def;
      SetNameSpace(def.defined_namespace);
      GenerateFwdDecl(def);
    } else if (type_def->enum_def) {
      const flatbuffers::EnumDef& def = *type_def->enum_def;
      SetNameSpace(def.defined_namespace);
      GenerateFwdDecl(def);
    }
  }

  for (auto type_def : types) {
    if (type_def->struct_def) {
      const flatbuffers::StructDef& def = *type_def->struct_def;
      SetNameSpace(def.defined_namespace);
      GenerateStructDecl(def);
    } else if (type_def->enum_def) {
      const flatbuffers::EnumDef& def = *type_def->enum_def;
      SetNameSpace(def.defined_namespace);
      GenerateEnumDecl(def);
    }
  }

  for (auto type_def : types) {
    if (type_def->struct_def) {
      const flatbuffers::StructDef& def = *type_def->struct_def;
      SetNameSpace(def.defined_namespace);
      GenerateStructFunctions(def);
    } else if (type_def->enum_def) {
      const flatbuffers::EnumDef& def = *type_def->enum_def;
      SetNameSpace(def.defined_namespace);
      GenerateEnumFunctions(def);
    }
  }

  SetNameSpace(&root_namespace_);
  code_ += "";

  for (auto type_def : types) {
    if (type_def->struct_def) {
      GenerateRegisterTypeId(*type_def->struct_def);
    } else if (type_def->enum_def) {
      GenerateRegisterTypeId(*type_def->enum_def);
    }
  }

  code_ += "";
  code_ += "#endif  // {{INCLUDE_GUARD}}";
  code_ += "";

  return flatbuffers::SaveFile(file_path.c_str(), code_.ToString(), false);
}

// Warning function required by flatc compiler.
static void Warn(const flatbuffers::FlatCompiler* flatc,
                 const std::string& warn, bool show_exe_name) {
  std::cout << "Warning: " << warn << std::endl;
}

// Error function required by flatc compiler.
static void Error(const flatbuffers::FlatCompiler* flatc,
                  const std::string& err, bool usage, bool show_exe_name) {
  std::cout << "Error: " << err << std::endl;
  exit(1);
}

// GenerateCode function required by flatc compiler.
static bool GenerateCode(const flatbuffers::Parser& parser,
                         const std::string& path,
                         const std::string& file_name) {
  CodeGenerator gen(parser, path, file_name);
  return gen.generate();
}

int main(int argc, const char* argv[]) {
  flatbuffers::FlatCompiler::Generator generator;
  generator.generate = GenerateCode;
  generator.generator_opt_long = "--experimental";
  generator.generator_opt_short = "-x";
  generator.lang_name = nullptr;
  generator.generateGRPC = nullptr;
  generator.generator_help = nullptr;
  generator.make_rule = nullptr;
  generator.lang = flatbuffers::IDLOptions::kMAX;

  flatbuffers::FlatCompiler::InitParams params;
  params.generators = &generator;
  params.num_generators = 1;
  params.warn_fn = Warn;
  params.error_fn = Error;

  std::vector<const char*> args;
  args.insert(args.end(), argv + 1, argv + argc);

  flatbuffers::FlatCompiler flatc(params);
  return static_cast<int>(
      flatc.Compile(static_cast<int>(args.size()), args.data()));
}
