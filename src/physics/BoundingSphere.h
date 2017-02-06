#pragma once

#include "Fixed.h"

enum class Type { BoundingSphere };

struct PhysicsObject {
  vec3f p0;
  quatf r0;
  vec3f p1;
  quatf r1;
  vec3f p2;
  quatf r2;
};

struct CollisionMesh {
};

struct CollisionTuple {
  CollisionMesh *a, *b;
};

class BoundingSphere : public CollisionMesh {
public:
  vec3f location;
  Fixed radius;
};


