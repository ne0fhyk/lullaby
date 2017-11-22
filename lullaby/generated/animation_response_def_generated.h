// Autogenerated code.  Do not edit.
#ifndef _LULLABY_LULLABY_GENERATED_ANIMATION_RESPONSE_DEF_GENERATED_H_
#define _LULLABY_LULLABY_GENERATED_ANIMATION_RESPONSE_DEF_GENERATED_H_

#include <type_traits>
#include <memory>
#include "flatbuffers/animation_response_def_generated.h"
#include "lullaby/util/common_types.h"
#include "lullaby/util/color.h"
#include "lullaby/util/math.h"
#include "lullaby/util/optional.h"
#include "lullaby/util/typeid.h"
#include "animation_def_generated.h"
#include "common_generated.h"
#include "dispatcher_def_generated.h"
#include "variant_def_generated.h"

namespace lull {
class AnimationResponseDefT;
class AnimationResponseDefT {
 public:
  using FlatBufferType = AnimationResponseDef;

  AnimationResponseDefT() {}

  std::vector<lull::EventDefT> inputs;
  lull::AnimationDefT animation;

  template <typename Archive>
  void SerializeFlatbuffer(Archive archive);
};

template <typename Archive>
void AnimationResponseDefT::SerializeFlatbuffer(Archive archive) {
  archive.VectorOfTables(&inputs, 4);
  archive.Table(&animation, 6);
}

}  // namespace lull

LULLABY_SETUP_TYPEID(lull::AnimationResponseDefT);

#endif  // _LULLABY_LULLABY_GENERATED_ANIMATION_RESPONSE_DEF_GENERATED_H_

