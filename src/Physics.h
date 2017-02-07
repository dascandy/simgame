#pragma once

#include "Fixed.h"
#include <vector>
#include <memory>

class Object;

enum class Type { BoundingSphere, WorldBox };

struct CollisionTuple {
  Object *a, *b;
};

struct CollisionMesh {
  CollisionMesh(Type type) : type(type) {}
  Type type;
};

struct BoundingSphere : public CollisionMesh {
public:
  BoundingSphere(Fixed radius) : CollisionMesh(Type::BoundingSphere), radius(radius) {}
  Fixed radius;
};

struct WorldBox : public CollisionMesh {
public:
  WorldBox(vec3f lower, vec3f upper) : CollisionMesh(Type::WorldBox), lower(lower), upper(upper) {}
  vec3f lower, upper;
};


struct PhysicsWorld {
  PhysicsWorld(Fixed ups = 60);
  Fixed ups;
  std::vector<Object*> objs;
  auto begin() { return objs.begin(); }
  auto end() { return objs.end(); }
  void Step();
  std::unique_ptr<WorldBox> worldbox;
};

