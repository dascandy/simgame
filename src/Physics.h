#pragma once

#include "Fixed.h"
#include <vector>

class Object;

enum class Type { BoundingSphere };

struct PhysicsWorld {
  PhysicsWorld(Fixed ups = 20);
  Fixed ups;
  std::vector<Object*> objs;
  auto begin() { return objs.begin(); }
  auto end() { return objs.end(); }
  void Step();
};

struct CollisionTuple {
  Object *a, *b;
};

struct CollisionMesh {
};

struct BoundingSphere : public CollisionMesh {
public:
  BoundingSphere(Fixed radius) : radius(radius) {}
private:
  Fixed radius;
};


