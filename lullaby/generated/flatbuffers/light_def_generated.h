// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_LIGHTDEF_LULL_H_
#define FLATBUFFERS_GENERATED_LIGHTDEF_LULL_H_

#include "flatbuffers/flatbuffers.h"

#include "common_generated.h"

namespace lull {

struct ShadowMapDef;

struct AmbientLightDef;

struct DirectionalLightDef;

struct PointLightDef;

struct LightableDef;

/// Union defining types of shadow implementations that may be used.
enum ShadowDef {
  ShadowDef_NONE = 0,
  ShadowDef_ShadowMapDef = 1,
  ShadowDef_MIN = ShadowDef_NONE,
  ShadowDef_MAX = ShadowDef_ShadowMapDef
};

inline ShadowDef (&EnumValuesShadowDef())[2] {
  static ShadowDef values[] = {
    ShadowDef_NONE,
    ShadowDef_ShadowMapDef
  };
  return values;
}

inline const char **EnumNamesShadowDef() {
  static const char *names[] = {
    "NONE",
    "ShadowMapDef",
    nullptr
  };
  return names;
}

inline const char *EnumNameShadowDef(ShadowDef e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesShadowDef()[index];
}

template<typename T> struct ShadowDefTraits {
  static const ShadowDef enum_value = ShadowDef_NONE;
};

template<> struct ShadowDefTraits<ShadowMapDef> {
  static const ShadowDef enum_value = ShadowDef_ShadowMapDef;
};

bool VerifyShadowDef(flatbuffers::Verifier &verifier, const void *obj, ShadowDef type);
bool VerifyShadowDefVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

/// Enum reflecting the interaction an object has with shadows. This may be
/// extended in the future.
enum ShadowInteraction {
  ShadowInteraction_None = 0,
  ShadowInteraction_CastAndReceive = 1,
  ShadowInteraction_MIN = ShadowInteraction_None,
  ShadowInteraction_MAX = ShadowInteraction_CastAndReceive
};

inline ShadowInteraction (&EnumValuesShadowInteraction())[2] {
  static ShadowInteraction values[] = {
    ShadowInteraction_None,
    ShadowInteraction_CastAndReceive
  };
  return values;
}

inline const char **EnumNamesShadowInteraction() {
  static const char *names[] = {
    "None",
    "CastAndReceive",
    nullptr
  };
  return names;
}

inline const char *EnumNameShadowInteraction(ShadowInteraction e) {
  const size_t index = static_cast<int>(e);
  return EnumNamesShadowInteraction()[index];
}

struct ShadowMapDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.ShadowMapDef";
  }
  enum {
    VT_SHADOW_RESOLUTION = 4,
    VT_SHADOW_MIN_DISTANCE = 6,
    VT_SHADOW_MAX_DISTANCE = 8,
    VT_SHADOW_VOLUME = 10
  };
  /// The resolution (in pixels) used for the shadow map texture. Higher
  /// resolution means better detail, but also increased performance cost.
  int32_t shadow_resolution() const {
    return GetField<int32_t>(VT_SHADOW_RESOLUTION, 512);
  }
  /// The minimum distance from the light for shadows to be captured. Lower
  /// value captures objects nearer the light point. Note that high
  /// |shadow_max_distance-shadow_min_distance| value increases chances for
  /// artifacts.
  float shadow_min_distance() const {
    return GetField<float>(VT_SHADOW_MIN_DISTANCE, 1.0f);
  }
  /// The maximum distance from the light for shadows to be captured. Higher
  /// value captures objects further away from the light point. Note that high
  /// |shadow_max_distance-shadow_min_distance| value increases chances for
  /// artifacts.
  float shadow_max_distance() const {
    return GetField<float>(VT_SHADOW_MAX_DISTANCE, 10.0f);
  }
  /// The volume of the shadow map, excluding the distance (used for the x and y
  /// components of the orthographic projection). Higher number captures more
  /// area, but reduces the detail captured per pixel.
  float shadow_volume() const {
    return GetField<float>(VT_SHADOW_VOLUME, 10.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_SHADOW_RESOLUTION) &&
           VerifyField<float>(verifier, VT_SHADOW_MIN_DISTANCE) &&
           VerifyField<float>(verifier, VT_SHADOW_MAX_DISTANCE) &&
           VerifyField<float>(verifier, VT_SHADOW_VOLUME) &&
           verifier.EndTable();
  }
};

struct ShadowMapDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_shadow_resolution(int32_t shadow_resolution) {
    fbb_.AddElement<int32_t>(ShadowMapDef::VT_SHADOW_RESOLUTION, shadow_resolution, 512);
  }
  void add_shadow_min_distance(float shadow_min_distance) {
    fbb_.AddElement<float>(ShadowMapDef::VT_SHADOW_MIN_DISTANCE, shadow_min_distance, 1.0f);
  }
  void add_shadow_max_distance(float shadow_max_distance) {
    fbb_.AddElement<float>(ShadowMapDef::VT_SHADOW_MAX_DISTANCE, shadow_max_distance, 10.0f);
  }
  void add_shadow_volume(float shadow_volume) {
    fbb_.AddElement<float>(ShadowMapDef::VT_SHADOW_VOLUME, shadow_volume, 10.0f);
  }
  explicit ShadowMapDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShadowMapDefBuilder &operator=(const ShadowMapDefBuilder &);
  flatbuffers::Offset<ShadowMapDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ShadowMapDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShadowMapDef> CreateShadowMapDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t shadow_resolution = 512,
    float shadow_min_distance = 1.0f,
    float shadow_max_distance = 10.0f,
    float shadow_volume = 10.0f) {
  ShadowMapDefBuilder builder_(_fbb);
  builder_.add_shadow_volume(shadow_volume);
  builder_.add_shadow_max_distance(shadow_max_distance);
  builder_.add_shadow_min_distance(shadow_min_distance);
  builder_.add_shadow_resolution(shadow_resolution);
  return builder_.Finish();
}

/// Defines an ambient light source.
struct AmbientLightDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.AmbientLightDef";
  }
  enum {
    VT_GROUP = 4,
    VT_COLOR = 6
  };
  /// The group of lights to which this light belongs.
  uint32_t group() const {
    return GetField<uint32_t>(VT_GROUP, 0);
  }
  /// The color of the ambient light.
  const Color *color() const {
    return GetStruct<const Color *>(VT_COLOR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_GROUP) &&
           VerifyField<Color>(verifier, VT_COLOR) &&
           verifier.EndTable();
  }
};

struct AmbientLightDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_group(uint32_t group) {
    fbb_.AddElement<uint32_t>(AmbientLightDef::VT_GROUP, group, 0);
  }
  void add_color(const Color *color) {
    fbb_.AddStruct(AmbientLightDef::VT_COLOR, color);
  }
  explicit AmbientLightDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AmbientLightDefBuilder &operator=(const AmbientLightDefBuilder &);
  flatbuffers::Offset<AmbientLightDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<AmbientLightDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<AmbientLightDef> CreateAmbientLightDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t group = 0,
    const Color *color = 0) {
  AmbientLightDefBuilder builder_(_fbb);
  builder_.add_color(color);
  builder_.add_group(group);
  return builder_.Finish();
}

/// Defines a directional light source.
struct DirectionalLightDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.DirectionalLightDef";
  }
  enum {
    VT_GROUP = 4,
    VT_COLOR = 6,
    VT_EXPONENT = 8,
    VT_SHADOW_DEF_TYPE = 10,
    VT_SHADOW_DEF = 12,
    VT_ROTATION = 14
  };
  /// The group of lights to which this light belongs.
  uint32_t group() const {
    return GetField<uint32_t>(VT_GROUP, 0);
  }
  /// The color of the directional light.
  const Color *color() const {
    return GetStruct<const Color *>(VT_COLOR);
  }
  /// The intensity of the directional light specular width.
  float exponent() const {
    return GetField<float>(VT_EXPONENT, 0.0f);
  }
  ShadowDef shadow_def_type() const {
    return static_cast<ShadowDef>(GetField<uint8_t>(VT_SHADOW_DEF_TYPE, 0));
  }
  /// Shadow implementation detail. Default is null (no shadow).
  const void *shadow_def() const {
    return GetPointer<const void *>(VT_SHADOW_DEF);
  }
  template<typename T> const T *shadow_def_as() const;
  const ShadowMapDef *shadow_def_as_ShadowMapDef() const {
    return shadow_def_type() == ShadowDef_ShadowMapDef ? static_cast<const ShadowMapDef *>(shadow_def()) : nullptr;
  }
  const Quat *rotation() const {
    return GetStruct<const Quat *>(VT_ROTATION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_GROUP) &&
           VerifyField<Color>(verifier, VT_COLOR) &&
           VerifyField<float>(verifier, VT_EXPONENT) &&
           VerifyField<uint8_t>(verifier, VT_SHADOW_DEF_TYPE) &&
           VerifyOffset(verifier, VT_SHADOW_DEF) &&
           VerifyShadowDef(verifier, shadow_def(), shadow_def_type()) &&
           VerifyField<Quat>(verifier, VT_ROTATION) &&
           verifier.EndTable();
  }
};

template<> inline const ShadowMapDef *DirectionalLightDef::shadow_def_as<ShadowMapDef>() const {
  return shadow_def_as_ShadowMapDef();
}

struct DirectionalLightDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_group(uint32_t group) {
    fbb_.AddElement<uint32_t>(DirectionalLightDef::VT_GROUP, group, 0);
  }
  void add_color(const Color *color) {
    fbb_.AddStruct(DirectionalLightDef::VT_COLOR, color);
  }
  void add_exponent(float exponent) {
    fbb_.AddElement<float>(DirectionalLightDef::VT_EXPONENT, exponent, 0.0f);
  }
  void add_shadow_def_type(ShadowDef shadow_def_type) {
    fbb_.AddElement<uint8_t>(DirectionalLightDef::VT_SHADOW_DEF_TYPE, static_cast<uint8_t>(shadow_def_type), 0);
  }
  void add_shadow_def(flatbuffers::Offset<void> shadow_def) {
    fbb_.AddOffset(DirectionalLightDef::VT_SHADOW_DEF, shadow_def);
  }
  void add_rotation(const Quat *rotation) {
    fbb_.AddStruct(DirectionalLightDef::VT_ROTATION, rotation);
  }
  explicit DirectionalLightDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  DirectionalLightDefBuilder &operator=(const DirectionalLightDefBuilder &);
  flatbuffers::Offset<DirectionalLightDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DirectionalLightDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<DirectionalLightDef> CreateDirectionalLightDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t group = 0,
    const Color *color = 0,
    float exponent = 0.0f,
    ShadowDef shadow_def_type = ShadowDef_NONE,
    flatbuffers::Offset<void> shadow_def = 0,
    const Quat *rotation = 0) {
  DirectionalLightDefBuilder builder_(_fbb);
  builder_.add_rotation(rotation);
  builder_.add_shadow_def(shadow_def);
  builder_.add_exponent(exponent);
  builder_.add_color(color);
  builder_.add_group(group);
  builder_.add_shadow_def_type(shadow_def_type);
  return builder_.Finish();
}

/// Defines a point light source.
struct PointLightDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.PointLightDef";
  }
  enum {
    VT_GROUP = 4,
    VT_COLOR = 6,
    VT_INTENSITY = 8,
    VT_EXPONENT = 10,
    VT_POSITION = 12
  };
  /// The group of lights to which this light belongs.
  uint32_t group() const {
    return GetField<uint32_t>(VT_GROUP, 0);
  }
  /// The color of the point light.
  const Color *color() const {
    return GetStruct<const Color *>(VT_COLOR);
  }
  /// The intensity of the point light.
  float intensity() const {
    return GetField<float>(VT_INTENSITY, 0.0f);
  }
  /// The intensity of the point light specular width.
  float exponent() const {
    return GetField<float>(VT_EXPONENT, 0.0f);
  }
  const Vec3 *position() const {
    return GetStruct<const Vec3 *>(VT_POSITION);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_GROUP) &&
           VerifyField<Color>(verifier, VT_COLOR) &&
           VerifyField<float>(verifier, VT_INTENSITY) &&
           VerifyField<float>(verifier, VT_EXPONENT) &&
           VerifyField<Vec3>(verifier, VT_POSITION) &&
           verifier.EndTable();
  }
};

struct PointLightDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_group(uint32_t group) {
    fbb_.AddElement<uint32_t>(PointLightDef::VT_GROUP, group, 0);
  }
  void add_color(const Color *color) {
    fbb_.AddStruct(PointLightDef::VT_COLOR, color);
  }
  void add_intensity(float intensity) {
    fbb_.AddElement<float>(PointLightDef::VT_INTENSITY, intensity, 0.0f);
  }
  void add_exponent(float exponent) {
    fbb_.AddElement<float>(PointLightDef::VT_EXPONENT, exponent, 0.0f);
  }
  void add_position(const Vec3 *position) {
    fbb_.AddStruct(PointLightDef::VT_POSITION, position);
  }
  explicit PointLightDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PointLightDefBuilder &operator=(const PointLightDefBuilder &);
  flatbuffers::Offset<PointLightDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PointLightDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<PointLightDef> CreatePointLightDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t group = 0,
    const Color *color = 0,
    float intensity = 0.0f,
    float exponent = 0.0f,
    const Vec3 *position = 0) {
  PointLightDefBuilder builder_(_fbb);
  builder_.add_position(position);
  builder_.add_exponent(exponent);
  builder_.add_intensity(intensity);
  builder_.add_color(color);
  builder_.add_group(group);
  return builder_.Finish();
}

/// Defines an Entity that can be "lit" by the lights in the associated group.
struct LightableDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.LightableDef";
  }
  enum {
    VT_GROUP = 4,
    VT_MAX_AMBIENT_LIGHTS = 6,
    VT_MAX_DIRECTIONAL_LIGHTS = 8,
    VT_MAX_POINT_LIGHTS = 10,
    VT_SHADOW_INTERACTION = 12,
    VT_SHADOW_SAMPLER = 14,
    VT_DEPTH_SHADER = 16
  };
  /// The group of lights that will be applied to this Entity.
  uint32_t group() const {
    return GetField<uint32_t>(VT_GROUP, 0);
  }
  /// The maximum number of ambient lights to apply to this Entity.
  int32_t max_ambient_lights() const {
    return GetField<int32_t>(VT_MAX_AMBIENT_LIGHTS, 0);
  }
  /// The maximum number of directional lights to apply to this Entity.
  int32_t max_directional_lights() const {
    return GetField<int32_t>(VT_MAX_DIRECTIONAL_LIGHTS, 0);
  }
  /// The maximum number of point lights to apply to this Entity.
  int32_t max_point_lights() const {
    return GetField<int32_t>(VT_MAX_POINT_LIGHTS, 0);
  }
  /// Is this lightable object a shadowcaster?
  ShadowInteraction shadow_interaction() const {
    return static_cast<ShadowInteraction>(GetField<int32_t>(VT_SHADOW_INTERACTION, 0));
  }
  /// The texture sampler for the shadow map texture. This should correspond to
  /// the value set for the sampler inside the shader.
  int32_t shadow_sampler() const {
    return GetField<int32_t>(VT_SHADOW_SAMPLER, 5);
  }
  /// Custom depth shader to use for rendering the shadow. If unset, default
  /// shader will be used.
  const flatbuffers::String *depth_shader() const {
    return GetPointer<const flatbuffers::String *>(VT_DEPTH_SHADER);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_GROUP) &&
           VerifyField<int32_t>(verifier, VT_MAX_AMBIENT_LIGHTS) &&
           VerifyField<int32_t>(verifier, VT_MAX_DIRECTIONAL_LIGHTS) &&
           VerifyField<int32_t>(verifier, VT_MAX_POINT_LIGHTS) &&
           VerifyField<int32_t>(verifier, VT_SHADOW_INTERACTION) &&
           VerifyField<int32_t>(verifier, VT_SHADOW_SAMPLER) &&
           VerifyOffset(verifier, VT_DEPTH_SHADER) &&
           verifier.Verify(depth_shader()) &&
           verifier.EndTable();
  }
};

struct LightableDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_group(uint32_t group) {
    fbb_.AddElement<uint32_t>(LightableDef::VT_GROUP, group, 0);
  }
  void add_max_ambient_lights(int32_t max_ambient_lights) {
    fbb_.AddElement<int32_t>(LightableDef::VT_MAX_AMBIENT_LIGHTS, max_ambient_lights, 0);
  }
  void add_max_directional_lights(int32_t max_directional_lights) {
    fbb_.AddElement<int32_t>(LightableDef::VT_MAX_DIRECTIONAL_LIGHTS, max_directional_lights, 0);
  }
  void add_max_point_lights(int32_t max_point_lights) {
    fbb_.AddElement<int32_t>(LightableDef::VT_MAX_POINT_LIGHTS, max_point_lights, 0);
  }
  void add_shadow_interaction(ShadowInteraction shadow_interaction) {
    fbb_.AddElement<int32_t>(LightableDef::VT_SHADOW_INTERACTION, static_cast<int32_t>(shadow_interaction), 0);
  }
  void add_shadow_sampler(int32_t shadow_sampler) {
    fbb_.AddElement<int32_t>(LightableDef::VT_SHADOW_SAMPLER, shadow_sampler, 5);
  }
  void add_depth_shader(flatbuffers::Offset<flatbuffers::String> depth_shader) {
    fbb_.AddOffset(LightableDef::VT_DEPTH_SHADER, depth_shader);
  }
  explicit LightableDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  LightableDefBuilder &operator=(const LightableDefBuilder &);
  flatbuffers::Offset<LightableDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<LightableDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<LightableDef> CreateLightableDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t group = 0,
    int32_t max_ambient_lights = 0,
    int32_t max_directional_lights = 0,
    int32_t max_point_lights = 0,
    ShadowInteraction shadow_interaction = ShadowInteraction_None,
    int32_t shadow_sampler = 5,
    flatbuffers::Offset<flatbuffers::String> depth_shader = 0) {
  LightableDefBuilder builder_(_fbb);
  builder_.add_depth_shader(depth_shader);
  builder_.add_shadow_sampler(shadow_sampler);
  builder_.add_shadow_interaction(shadow_interaction);
  builder_.add_max_point_lights(max_point_lights);
  builder_.add_max_directional_lights(max_directional_lights);
  builder_.add_max_ambient_lights(max_ambient_lights);
  builder_.add_group(group);
  return builder_.Finish();
}

inline flatbuffers::Offset<LightableDef> CreateLightableDefDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t group = 0,
    int32_t max_ambient_lights = 0,
    int32_t max_directional_lights = 0,
    int32_t max_point_lights = 0,
    ShadowInteraction shadow_interaction = ShadowInteraction_None,
    int32_t shadow_sampler = 5,
    const char *depth_shader = nullptr) {
  return lull::CreateLightableDef(
      _fbb,
      group,
      max_ambient_lights,
      max_directional_lights,
      max_point_lights,
      shadow_interaction,
      shadow_sampler,
      depth_shader ? _fbb.CreateString(depth_shader) : 0);
}

inline bool VerifyShadowDef(flatbuffers::Verifier &verifier, const void *obj, ShadowDef type) {
  switch (type) {
    case ShadowDef_NONE: {
      return true;
    }
    case ShadowDef_ShadowMapDef: {
      auto ptr = reinterpret_cast<const ShadowMapDef *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return false;
  }
}

inline bool VerifyShadowDefVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyShadowDef(
        verifier,  values->Get(i), types->GetEnum<ShadowDef>(i))) {
      return false;
    }
  }
  return true;
}

}  // namespace lull

#endif  // FLATBUFFERS_GENERATED_LIGHTDEF_LULL_H_
