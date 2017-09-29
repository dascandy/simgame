#pragma once

#include <glm.h>

class Model;

class Object {
public:
  Object(Model* model, vec3 pos, quat rot);
  void AddForce(vec3 force);
public:
  Model* model;
  vec3 p0;
  quat r0;
  vec3 p1;
  quat r1;
  vec3 p2;
  quat r2;
  float mass;
};

