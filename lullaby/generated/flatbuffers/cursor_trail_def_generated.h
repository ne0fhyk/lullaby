// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CURSORTRAILDEF_LULL_H_
#define FLATBUFFERS_GENERATED_CURSORTRAILDEF_LULL_H_

#include "flatbuffers/flatbuffers.h"

#include "common_generated.h"

namespace lull {

struct CursorTrailDef;

/// Configures the cursor trail.
/// In case of changing any of these values, please update reticle_template.fbs.
struct CursorTrailDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.CursorTrailDef";
  }
  enum {
    VT_AVERAGE_TRAIL_LENGTH = 4,
    VT_QUAD_SIZE = 6,
    VT_CURVE_SAMPLES = 8,
    VT_AVERAGE_SPEED = 10,
    VT_DEFAULT_COLOR = 12,
    VT_MAX_TRAIL_LENGTH = 14
  };
  /// The number of cursors to draw in the trail by default
  int32_t average_trail_length() const {
    return GetField<int32_t>(VT_AVERAGE_TRAIL_LENGTH, 14);
  }
  /// The size of the cursor quad
  float quad_size() const {
    return GetField<float>(VT_QUAD_SIZE, 0.05f);
  }
  /// The number of samples from which to create the interpolating curve
  int32_t curve_samples() const {
    return GetField<int32_t>(VT_CURVE_SAMPLES, 4);
  }
  /// Speed of the cursor at which the number of cursors drawn = trail_length
  float average_speed() const {
    return GetField<float>(VT_AVERAGE_SPEED, 0.2f);
  }
  /// Default cursor color
  const Color *default_color() const {
    return GetStruct<const Color *>(VT_DEFAULT_COLOR);
  }
  /// Max number of cursors to draw. If this limit is reached the cursor trail
  /// will become sparser.
  int32_t max_trail_length() const {
    return GetField<int32_t>(VT_MAX_TRAIL_LENGTH, 32);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_AVERAGE_TRAIL_LENGTH) &&
           VerifyField<float>(verifier, VT_QUAD_SIZE) &&
           VerifyField<int32_t>(verifier, VT_CURVE_SAMPLES) &&
           VerifyField<float>(verifier, VT_AVERAGE_SPEED) &&
           VerifyField<Color>(verifier, VT_DEFAULT_COLOR) &&
           VerifyField<int32_t>(verifier, VT_MAX_TRAIL_LENGTH) &&
           verifier.EndTable();
  }
};

struct CursorTrailDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_average_trail_length(int32_t average_trail_length) {
    fbb_.AddElement<int32_t>(CursorTrailDef::VT_AVERAGE_TRAIL_LENGTH, average_trail_length, 14);
  }
  void add_quad_size(float quad_size) {
    fbb_.AddElement<float>(CursorTrailDef::VT_QUAD_SIZE, quad_size, 0.05f);
  }
  void add_curve_samples(int32_t curve_samples) {
    fbb_.AddElement<int32_t>(CursorTrailDef::VT_CURVE_SAMPLES, curve_samples, 4);
  }
  void add_average_speed(float average_speed) {
    fbb_.AddElement<float>(CursorTrailDef::VT_AVERAGE_SPEED, average_speed, 0.2f);
  }
  void add_default_color(const Color *default_color) {
    fbb_.AddStruct(CursorTrailDef::VT_DEFAULT_COLOR, default_color);
  }
  void add_max_trail_length(int32_t max_trail_length) {
    fbb_.AddElement<int32_t>(CursorTrailDef::VT_MAX_TRAIL_LENGTH, max_trail_length, 32);
  }
  explicit CursorTrailDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CursorTrailDefBuilder &operator=(const CursorTrailDefBuilder &);
  flatbuffers::Offset<CursorTrailDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CursorTrailDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<CursorTrailDef> CreateCursorTrailDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t average_trail_length = 14,
    float quad_size = 0.05f,
    int32_t curve_samples = 4,
    float average_speed = 0.2f,
    const Color *default_color = 0,
    int32_t max_trail_length = 32) {
  CursorTrailDefBuilder builder_(_fbb);
  builder_.add_max_trail_length(max_trail_length);
  builder_.add_default_color(default_color);
  builder_.add_average_speed(average_speed);
  builder_.add_curve_samples(curve_samples);
  builder_.add_quad_size(quad_size);
  builder_.add_average_trail_length(average_trail_length);
  return builder_.Finish();
}

inline const lull::CursorTrailDef *GetCursorTrailDef(const void *buf) {
  return flatbuffers::GetRoot<lull::CursorTrailDef>(buf);
}

inline bool VerifyCursorTrailDefBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<lull::CursorTrailDef>(nullptr);
}

inline void FinishCursorTrailDefBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<lull::CursorTrailDef> root) {
  fbb.Finish(root);
}

}  // namespace lull

#endif  // FLATBUFFERS_GENERATED_CURSORTRAILDEF_LULL_H_
