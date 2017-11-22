// Autogenerated code.  Do not edit.
#ifndef _LULLABY_LULLABY_GENERATED_COMMON_GENERATED_H_
#define _LULLABY_LULLABY_GENERATED_COMMON_GENERATED_H_

#include <type_traits>
#include <memory>
#include "flatbuffers/common_generated.h"
#include "lullaby/util/common_types.h"
#include "lullaby/util/color.h"
#include "lullaby/util/math.h"
#include "lullaby/util/optional.h"
#include "lullaby/util/typeid.h"

namespace lull {
class ArcDefT;
class ArcDefT {
 public:
  using FlatBufferType = ArcDef;

  ArcDefT() {}

  float start_angle = 0.0f;
  float angle_size = 0.0f;
  float inner_radius = 0.0f;
  float outer_radius = 0.0f;
  int32_t num_samples = 0;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

template <typename Archive>
void ArcDefT::SerializeFlatbuffer(Archive archive) {
  archive.Scalar(&start_angle, 0, 0.0f);
  archive.Scalar(&angle_size, 4, 0.0f);
  archive.Scalar(&inner_radius, 8, 0.0f);
  archive.Scalar(&outer_radius, 12, 0.0f);
  archive.Scalar(&num_samples, 16, 0);
}

}  // namespace lull

LULLABY_SETUP_TYPEID(lull::ArcDefT);
LULLABY_SETUP_TYPEID(lull::LayoutFillOrder);
LULLABY_SETUP_TYPEID(lull::LayoutHorizontalAlignment);
LULLABY_SETUP_TYPEID(lull::LayoutVerticalAlignment);
LULLABY_SETUP_TYPEID(lull::DeviceType);

#endif  // _LULLABY_LULLABY_GENERATED_COMMON_GENERATED_H_

