// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_COLLISIONDEF_LULL_H_
#define FLATBUFFERS_GENERATED_COLLISIONDEF_LULL_H_

#include "flatbuffers/flatbuffers.h"

#include "common_generated.h"

namespace lull {

struct CollisionDef;

struct CollisionClipBoundsDef;

/// When *CollisionDef* is specified, the entity is included in the
/// CollisionSystem, which enables a raycast test to find the nearest entity
/// which is intersecting a Ray.
struct CollisionDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.CollisionDef";
  }
  enum {
    VT_COLLISION_ON_EXIT = 4,
    VT_INTERACTIVE = 6,
    VT_CLIP_OUTSIDE_BOUNDS = 8
  };
  /// If set to false (default), the ray-bounding box intersection test will
  /// return the point where the ray enters the bounding box.
  /// If set to true, the point where the ray exists the bounding box will be
  /// returned instead.
  /// The purpose of this mode is to easily enable collisions for small objects
  /// within the bounding box of a larger object by setting the larger object
  /// to collision_on_exit mode.
  bool collision_on_exit() const {
    return GetField<uint8_t>(VT_COLLISION_ON_EXIT, 0) != 0;
  }
  /// If set to true, the Entity will be interactive (ie. you can click on
  /// the entity with the reticle).
  bool interactive() const {
    return GetField<uint8_t>(VT_INTERACTIVE, 1) != 0;
  }
  /// If true, only detect collisions within the specified |aabb| from the
  /// nearest ancestor with CollisionClipBoundsDef.
  /// If no CollisionClipBoundsDef can be found then all collisions are allowed as
  /// normal.
  bool clip_outside_bounds() const {
    return GetField<uint8_t>(VT_CLIP_OUTSIDE_BOUNDS, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_COLLISION_ON_EXIT) &&
           VerifyField<uint8_t>(verifier, VT_INTERACTIVE) &&
           VerifyField<uint8_t>(verifier, VT_CLIP_OUTSIDE_BOUNDS) &&
           verifier.EndTable();
  }
};

struct CollisionDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_collision_on_exit(bool collision_on_exit) {
    fbb_.AddElement<uint8_t>(CollisionDef::VT_COLLISION_ON_EXIT, static_cast<uint8_t>(collision_on_exit), 0);
  }
  void add_interactive(bool interactive) {
    fbb_.AddElement<uint8_t>(CollisionDef::VT_INTERACTIVE, static_cast<uint8_t>(interactive), 1);
  }
  void add_clip_outside_bounds(bool clip_outside_bounds) {
    fbb_.AddElement<uint8_t>(CollisionDef::VT_CLIP_OUTSIDE_BOUNDS, static_cast<uint8_t>(clip_outside_bounds), 0);
  }
  explicit CollisionDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CollisionDefBuilder &operator=(const CollisionDefBuilder &);
  flatbuffers::Offset<CollisionDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CollisionDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<CollisionDef> CreateCollisionDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    bool collision_on_exit = false,
    bool interactive = true,
    bool clip_outside_bounds = false) {
  CollisionDefBuilder builder_(_fbb);
  builder_.add_clip_outside_bounds(clip_outside_bounds);
  builder_.add_interactive(interactive);
  builder_.add_collision_on_exit(collision_on_exit);
  return builder_.Finish();
}

/// Add CollisionClipBoundsDef to entities that are ancestors to entities with
/// CollisionDef.
struct CollisionClipBoundsDef FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  static FLATBUFFERS_CONSTEXPR const char *GetFullyQualifiedName() {
    return "lull.CollisionClipBoundsDef";
  }
  enum {
    VT_AABB = 4
  };
  /// This aabb will be interpreted in this entities local coordinate space.
  const AabbDef *aabb() const {
    return GetStruct<const AabbDef *>(VT_AABB);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<AabbDef>(verifier, VT_AABB) &&
           verifier.EndTable();
  }
};

struct CollisionClipBoundsDefBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_aabb(const AabbDef *aabb) {
    fbb_.AddStruct(CollisionClipBoundsDef::VT_AABB, aabb);
  }
  explicit CollisionClipBoundsDefBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CollisionClipBoundsDefBuilder &operator=(const CollisionClipBoundsDefBuilder &);
  flatbuffers::Offset<CollisionClipBoundsDef> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CollisionClipBoundsDef>(end);
    return o;
  }
};

inline flatbuffers::Offset<CollisionClipBoundsDef> CreateCollisionClipBoundsDef(
    flatbuffers::FlatBufferBuilder &_fbb,
    const AabbDef *aabb = 0) {
  CollisionClipBoundsDefBuilder builder_(_fbb);
  builder_.add_aabb(aabb);
  return builder_.Finish();
}

inline const lull::CollisionDef *GetCollisionDef(const void *buf) {
  return flatbuffers::GetRoot<lull::CollisionDef>(buf);
}

inline bool VerifyCollisionDefBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<lull::CollisionDef>(nullptr);
}

inline void FinishCollisionDefBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<lull::CollisionDef> root) {
  fbb.Finish(root);
}

}  // namespace lull

#endif  // FLATBUFFERS_GENERATED_COLLISIONDEF_LULL_H_
