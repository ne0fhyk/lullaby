// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_AUDIOLISTENERDEF_LULL_H_
#define FLATBUFFERS_GENERATED_AUDIOLISTENERDEF_LULL_H_

#include "flatbuffers/flatbuffers.h"

#include "common_generated.h"

namespace lull {

struct AudioListenerDef;

struct AudioListenerDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.AudioListenerDef";
  }
  enum {
    VT_INITIAL_VOLUME = 4
  };
  /// The initial master volume level, in the range [0,1.0].
  float initial_volume() const {
    return GetField<float>(VT_INITIAL_VOLUME, 1.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_INITIAL_VOLUME) &&
           verifier.EndTable();
  }
};

struct AudioListenerDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_initial_volume(float initial_volume) {
    fbb_.AddElement<float>(AudioListenerDef::VT_INITIAL_VOLUME, initial_volume, 1.0f);
  }
  explicit AudioListenerDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AudioListenerDefBuilder &operator=(const AudioListenerDefBuilder &);
  flatbuffers::Offset<AudioListenerDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<AudioListenerDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<AudioListenerDef> CreateAudioListenerDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    float initial_volume = 1.0f) {
  AudioListenerDefBuilder builder_(_fbb);
  builder_.add_initial_volume(initial_volume);
  return builder_.Finish();
}

inline const lull::AudioListenerDef *GetAudioListenerDef(const void *buf) {
  return flatbuffers::GetRoot<lull::AudioListenerDef>(buf);
}

inline bool VerifyAudioListenerDefBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<lull::AudioListenerDef>(nullptr);
}

inline void FinishAudioListenerDefBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<lull::AudioListenerDef> root) {
  fbb.Finish(root);
}

}  // namespace lull

#endif  // FLATBUFFERS_GENERATED_AUDIOLISTENERDEF_LULL_H_
