#include "Object.h"

Object::Object(Model* model, vec3 pos, quat rot) 
: model(model)
, p0(pos)
, r0(rot)
, mass(1)
{}

void Object::AddForce(vec3 force) {
  p2 += force / mass;
}


