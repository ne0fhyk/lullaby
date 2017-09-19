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


#ifndef FLATBUFFERS_GENERATED_SPLINEANIM_MOTIVE_H_
#define FLATBUFFERS_GENERATED_SPLINEANIM_MOTIVE_H_

#include "flatbuffers/flatbuffers.h"

#include "compact_spline_generated.h"

namespace motive {

struct CompactSplineAnimFloatFb;

struct CompactSplineAnimFloatFb FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SPLINES = 4
  };
  const flatbuffers::Vector<flatbuffers::Offset<motive::CompactSplineFloatFb>> *splines() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<motive::CompactSplineFloatFb>> *>(VT_SPLINES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_SPLINES) &&
           verifier.Verify(splines()) &&
           verifier.VerifyVectorOfTables(splines()) &&
           verifier.EndTable();
  }
};

struct CompactSplineAnimFloatFbBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_splines(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<motive::CompactSplineFloatFb>>> splines) {
    fbb_.AddOffset(CompactSplineAnimFloatFb::VT_SPLINES, splines);
  }
  CompactSplineAnimFloatFbBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CompactSplineAnimFloatFbBuilder &operator=(const CompactSplineAnimFloatFbBuilder &);
  flatbuffers::Offset<CompactSplineAnimFloatFb> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<CompactSplineAnimFloatFb>(end);
    return o;
  }
};

inline flatbuffers::Offset<CompactSplineAnimFloatFb> CreateCompactSplineAnimFloatFb(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<motive::CompactSplineFloatFb>>> splines = 0) {
  CompactSplineAnimFloatFbBuilder builder_(_fbb);
  builder_.add_splines(splines);
  return builder_.Finish();
}

inline flatbuffers::Offset<CompactSplineAnimFloatFb> CreateCompactSplineAnimFloatFbDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<motive::CompactSplineFloatFb>> *splines = nullptr) {
  return motive::CreateCompactSplineAnimFloatFb(
      _fbb,
      splines ? _fbb.CreateVector<flatbuffers::Offset<motive::CompactSplineFloatFb>>(*splines) : 0);
}

inline const motive::CompactSplineAnimFloatFb *GetCompactSplineAnimFloatFb(const void *buf) {
  return flatbuffers::GetRoot<motive::CompactSplineAnimFloatFb>(buf);
}

inline const char *CompactSplineAnimFloatFbIdentifier() {
  return "SPLN";
}

inline bool CompactSplineAnimFloatFbBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, CompactSplineAnimFloatFbIdentifier());
}

inline bool VerifyCompactSplineAnimFloatFbBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<motive::CompactSplineAnimFloatFb>(CompactSplineAnimFloatFbIdentifier());
}

inline const char *CompactSplineAnimFloatFbExtension() {
  return "motivespline";
}

inline void FinishCompactSplineAnimFloatFbBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<motive::CompactSplineAnimFloatFb> root) {
  fbb.Finish(root, CompactSplineAnimFloatFbIdentifier());
}

}  // namespace motive

#endif  // FLATBUFFERS_GENERATED_SPLINEANIM_MOTIVE_H_
