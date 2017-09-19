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

// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ANIM_MOTIVE_H_
#define FLATBUFFERS_GENERATED_ANIM_MOTIVE_H_

#include "flatbuffers/flatbuffers.h"

#include "compact_spline_generated.h"

namespace motive {

struct ConstantOpFb;

struct MatrixOpFb;

struct MatrixAnimFb;

struct RigAnimFb;

enum MatrixOperationTypeFb {
  MatrixOperationTypeFb_kInvalidMatrixOperation = 0,
  MatrixOperationTypeFb_kRotateAboutX = 1,
  MatrixOperationTypeFb_kRotateAboutY = 2,
  MatrixOperationTypeFb_kRotateAboutZ = 3,
  MatrixOperationTypeFb_kTranslateX = 4,
  MatrixOperationTypeFb_kTranslateY = 5,
  MatrixOperationTypeFb_kTranslateZ = 6,
  MatrixOperationTypeFb_kScaleX = 7,
  MatrixOperationTypeFb_kScaleY = 8,
  MatrixOperationTypeFb_kScaleZ = 9,
  MatrixOperationTypeFb_kScaleUniformly = 10,
  MatrixOperationTypeFb_kNumMatrixOperationTypes = 11,
  MatrixOperationTypeFb_MIN = MatrixOperationTypeFb_kInvalidMatrixOperation,
  MatrixOperationTypeFb_MAX = MatrixOperationTypeFb_kNumMatrixOperationTypes
};

inline MatrixOperationTypeFb (&EnumValuesMatrixOperationTypeFb())[12] {
  static MatrixOperationTypeFb values[] = {
    MatrixOperationTypeFb_kInvalidMatrixOperation,
    MatrixOperationTypeFb_kRotateAboutX,
    MatrixOperationTypeFb_kRotateAboutY,
    MatrixOperationTypeFb_kRotateAboutZ,
    MatrixOperationTypeFb_kTranslateX,
    MatrixOperationTypeFb_kTranslateY,
    MatrixOperationTypeFb_kTranslateZ,
    MatrixOperationTypeFb_kScaleX,
    MatrixOperationTypeFb_kScaleY,
    MatrixOperationTypeFb_kScaleZ,
    MatrixOperationTypeFb_kScaleUniformly,
    MatrixOperationTypeFb_kNumMatrixOperationTypes
  };
  return values;
}

inline const char **EnumNamesMatrixOperationTypeFb() {
  static const char *names[] = {
    "kInvalidMatrixOperation",
    "kRotateAboutX",
    "kRotateAboutY",
    "kRotateAboutZ",
    "kTranslateX",
    "kTranslateY",
    "kTranslateZ",
    "kScaleX",
    "kScaleY",
    "kScaleZ",
    "kScaleUniformly",
    "kNumMatrixOperationTypes",
    nullptr
  };
  return names;
}

inline const char *EnumNameMatrixOperationTypeFb(MatrixOperationTypeFb e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesMatrixOperationTypeFb()[index];
}

enum MatrixOpValueFb {
  MatrixOpValueFb_NONE = 0,
  MatrixOpValueFb_CompactSplineFb = 1,
  MatrixOpValueFb_ConstantOpFb = 2,
  MatrixOpValueFb_MIN = MatrixOpValueFb_NONE,
  MatrixOpValueFb_MAX = MatrixOpValueFb_ConstantOpFb
};

inline MatrixOpValueFb (&EnumValuesMatrixOpValueFb())[3] {
  static MatrixOpValueFb values[] = {
    MatrixOpValueFb_NONE,
    MatrixOpValueFb_CompactSplineFb,
    MatrixOpValueFb_ConstantOpFb
  };
  return values;
}

inline const char **EnumNamesMatrixOpValueFb() {
  static const char *names[] = {
    "NONE",
    "CompactSplineFb",
    "ConstantOpFb",
    nullptr
  };
  return names;
}

inline const char *EnumNameMatrixOpValueFb(MatrixOpValueFb e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesMatrixOpValueFb()[index];
}

template<typename T> struct MatrixOpValueFbTraits {
  static const MatrixOpValueFb enum_value = MatrixOpValueFb_NONE;
};

template<> struct MatrixOpValueFbTraits<motive::CompactSplineFb> {
  static const MatrixOpValueFb enum_value = MatrixOpValueFb_CompactSplineFb;
};

template<> struct MatrixOpValueFbTraits<ConstantOpFb> {
  static const MatrixOpValueFb enum_value = MatrixOpValueFb_ConstantOpFb;
};

bool VerifyMatrixOpValueFb(flatbuffers::Verifier &verifier, const void *obj, MatrixOpValueFb type);
bool VerifyMatrixOpValueFbVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct ConstantOpFb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_Y_CONST = 4
  };
  float y_const() const {
    return GetField<float>(VT_Y_CONST, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_Y_CONST) &&
           verifier.EndTable();
  }
};

struct ConstantOpFbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_y_const(float y_const) {
    fbb_.AddElement<float>(ConstantOpFb::VT_Y_CONST, y_const, 0.0f);
  }
  ConstantOpFbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ConstantOpFbBuilder &operator=(const ConstantOpFbBuilder &);
  flatbuffers::Offset<ConstantOpFb> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ConstantOpFb>(end);
    return o;
  }
};

inline flatbuffers::Offset<ConstantOpFb> CreateConstantOpFb(
    flatbuffers::FlatBufferBuilder &_fbb,
    float y_const = 0.0f) {
  ConstantOpFbBuilder builder_(_fbb);
  builder_.add_y_const(y_const);
  return builder_.Finish();
}

struct MatrixOpFb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_TYPE = 6,
    VT_VALUE_TYPE = 8,
    VT_VALUE = 10
  };
  int8_t id() const {
    return GetField<int8_t>(VT_ID, 0);
  }
  MatrixOperationTypeFb type() const {
    return static_cast<MatrixOperationTypeFb>(GetField<int8_t>(VT_TYPE, 0));
  }
  MatrixOpValueFb value_type() const {
    return static_cast<MatrixOpValueFb>(GetField<uint8_t>(VT_VALUE_TYPE, 0));
  }
  const void *value() const {
    return GetPointer<const void *>(VT_VALUE);
  }
  template<typename T> const T *value_as() const;
  const motive::CompactSplineFb *value_as_CompactSplineFb() const {
    return value_type() == MatrixOpValueFb_CompactSplineFb ? static_cast<const motive::CompactSplineFb *>(value()) : nullptr;
  }
  const ConstantOpFb *value_as_ConstantOpFb() const {
    return value_type() == MatrixOpValueFb_ConstantOpFb ? static_cast<const ConstantOpFb *>(value()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_ID) &&
           VerifyField<int8_t>(verifier, VT_TYPE) &&
           VerifyField<uint8_t>(verifier, VT_VALUE_TYPE) &&
           VerifyOffset(verifier, VT_VALUE) &&
           VerifyMatrixOpValueFb(verifier, value(), value_type()) &&
           verifier.EndTable();
  }
};

template<> inline const motive::CompactSplineFb *MatrixOpFb::value_as<motive::CompactSplineFb>() const {
  return value_as_CompactSplineFb();
}

template<> inline const ConstantOpFb *MatrixOpFb::value_as<ConstantOpFb>() const {
  return value_as_ConstantOpFb();
}

struct MatrixOpFbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(int8_t id) {
    fbb_.AddElement<int8_t>(MatrixOpFb::VT_ID, id, 0);
  }
  void add_type(MatrixOperationTypeFb type) {
    fbb_.AddElement<int8_t>(MatrixOpFb::VT_TYPE, static_cast<int8_t>(type), 0);
  }
  void add_value_type(MatrixOpValueFb value_type) {
    fbb_.AddElement<uint8_t>(MatrixOpFb::VT_VALUE_TYPE, static_cast<uint8_t>(value_type), 0);
  }
  void add_value(flatbuffers::Offset<void> value) {
    fbb_.AddOffset(MatrixOpFb::VT_VALUE, value);
  }
  MatrixOpFbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MatrixOpFbBuilder &operator=(const MatrixOpFbBuilder &);
  flatbuffers::Offset<MatrixOpFb> Finish() {
    const auto end = fbb_.EndTable(start_, 4);
    auto o = flatbuffers::Offset<MatrixOpFb>(end);
    return o;
  }
};

inline flatbuffers::Offset<MatrixOpFb> CreateMatrixOpFb(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t id = 0,
    MatrixOperationTypeFb type = MatrixOperationTypeFb_kInvalidMatrixOperation,
    MatrixOpValueFb value_type = MatrixOpValueFb_NONE,
    flatbuffers::Offset<void> value = 0) {
  MatrixOpFbBuilder builder_(_fbb);
  builder_.add_value(value);
  builder_.add_value_type(value_type);
  builder_.add_type(type);
  builder_.add_id(id);
  return builder_.Finish();
}

struct MatrixAnimFb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_OPS = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<MatrixOpFb>> *ops() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MatrixOpFb>> *>(VT_OPS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_OPS) &&
           verifier.Verify(ops()) &&
           verifier.VerifyVectorOfTables(ops()) &&
           verifier.EndTable();
  }
};

struct MatrixAnimFbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_ops(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MatrixOpFb>>> ops) {
    fbb_.AddOffset(MatrixAnimFb::VT_OPS, ops);
  }
  MatrixAnimFbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  MatrixAnimFbBuilder &operator=(const MatrixAnimFbBuilder &);
  flatbuffers::Offset<MatrixAnimFb> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<MatrixAnimFb>(end);
    return o;
  }
};

inline flatbuffers::Offset<MatrixAnimFb> CreateMatrixAnimFb(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MatrixOpFb>>> ops = 0) {
  MatrixAnimFbBuilder builder_(_fbb);
  builder_.add_ops(ops);
  return builder_.Finish();
}

inline flatbuffers::Offset<MatrixAnimFb> CreateMatrixAnimFbDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<MatrixOpFb>> *ops = nullptr) {
  return motive::CreateMatrixAnimFb(
      _fbb,
      ops ? _fbb.CreateVector<flatbuffers::Offset<MatrixOpFb>>(*ops) : 0);
}

struct RigAnimFb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MATRIX_ANIMS = 4,
    VT_BONE_PARENTS = 6,
    VT_BONE_NAMES = 8,
    VT_REPEAT = 10,
    VT_NAME = 12
  };
  const flatbuffers::Vector<flatbuffers::Offset<MatrixAnimFb>> *matrix_anims() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<MatrixAnimFb>> *>(VT_MATRIX_ANIMS);
  }
  const flatbuffers::Vector<uint8_t> *bone_parents() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_BONE_PARENTS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *bone_names() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_BONE_NAMES);
  }
  bool repeat() const {
    return GetField<uint8_t>(VT_REPEAT, 0) != 0;
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_MATRIX_ANIMS) &&
           verifier.Verify(matrix_anims()) &&
           verifier.VerifyVectorOfTables(matrix_anims()) &&
           VerifyOffset(verifier, VT_BONE_PARENTS) &&
           verifier.Verify(bone_parents()) &&
           VerifyOffset(verifier, VT_BONE_NAMES) &&
           verifier.Verify(bone_names()) &&
           verifier.VerifyVectorOfStrings(bone_names()) &&
           VerifyField<uint8_t>(verifier, VT_REPEAT) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.Verify(name()) &&
           verifier.EndTable();
  }
};

struct RigAnimFbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_matrix_anims(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MatrixAnimFb>>> matrix_anims) {
    fbb_.AddOffset(RigAnimFb::VT_MATRIX_ANIMS, matrix_anims);
  }
  void add_bone_parents(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> bone_parents) {
    fbb_.AddOffset(RigAnimFb::VT_BONE_PARENTS, bone_parents);
  }
  void add_bone_names(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> bone_names) {
    fbb_.AddOffset(RigAnimFb::VT_BONE_NAMES, bone_names);
  }
  void add_repeat(bool repeat) {
    fbb_.AddElement<uint8_t>(RigAnimFb::VT_REPEAT, static_cast<uint8_t>(repeat), 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(RigAnimFb::VT_NAME, name);
  }
  RigAnimFbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RigAnimFbBuilder &operator=(const RigAnimFbBuilder &);
  flatbuffers::Offset<RigAnimFb> Finish() {
    const auto end = fbb_.EndTable(start_, 5);
    auto o = flatbuffers::Offset<RigAnimFb>(end);
    return o;
  }
};

inline flatbuffers::Offset<RigAnimFb> CreateRigAnimFb(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<MatrixAnimFb>>> matrix_anims = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> bone_parents = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> bone_names = 0,
    bool repeat = false,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  RigAnimFbBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_bone_names(bone_names);
  builder_.add_bone_parents(bone_parents);
  builder_.add_matrix_anims(matrix_anims);
  builder_.add_repeat(repeat);
  return builder_.Finish();
}

inline flatbuffers::Offset<RigAnimFb> CreateRigAnimFbDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<MatrixAnimFb>> *matrix_anims = nullptr,
    const std::vector<uint8_t> *bone_parents = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *bone_names = nullptr,
    bool repeat = false,
    const char *name = nullptr) {
  return motive::CreateRigAnimFb(
      _fbb,
      matrix_anims ? _fbb.CreateVector<flatbuffers::Offset<MatrixAnimFb>>(*matrix_anims) : 0,
      bone_parents ? _fbb.CreateVector<uint8_t>(*bone_parents) : 0,
      bone_names ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*bone_names) : 0,
      repeat,
      name ? _fbb.CreateString(name) : 0);
}

inline bool VerifyMatrixOpValueFb(flatbuffers::Verifier &verifier, const void *obj, MatrixOpValueFb type) {
  switch (type) {
    case MatrixOpValueFb_NONE: {
      return true;
    }
    case MatrixOpValueFb_CompactSplineFb: {
      auto ptr = reinterpret_cast<const motive::CompactSplineFb *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case MatrixOpValueFb_ConstantOpFb: {
      auto ptr = reinterpret_cast<const ConstantOpFb *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyMatrixOpValueFbVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyMatrixOpValueFb(
        verifier,  values->Get(i), types->GetEnum<MatrixOpValueFb>(i))) {
      return false;
    }
  }
  return true;
}

inline const motive::RigAnimFb *GetRigAnimFb(const void *buf) {
  return flatbuffers::GetRoot<motive::RigAnimFb>(buf);
}

inline const char *RigAnimFbIdentifier() {
  return "ANIM";
}

inline bool RigAnimFbBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, RigAnimFbIdentifier());
}

inline bool VerifyRigAnimFbBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<motive::RigAnimFb>(RigAnimFbIdentifier());
}

inline const char *RigAnimFbExtension() {
  return "motiveanim";
}

inline void FinishRigAnimFbBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<motive::RigAnimFb> root) {
  fbb.Finish(root, RigAnimFbIdentifier());
}

}  // namespace motive

#endif  // FLATBUFFERS_GENERATED_ANIM_MOTIVE_H_