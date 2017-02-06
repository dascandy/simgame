#pragma once

#include "Fixed.h"
class Model;

class Object {
public:
  Object(Model* model, vec3f pos, quatf rot);
  void AddForce(vec3f force);
  void StepPhysics(Fixed step);
public:
  Model* model;
  vec3f p0;
  quatf r0;
  vec3f p1;
  quatf r1;
  vec3f p2;
  quatf r2;
  Fixed mass;
};

