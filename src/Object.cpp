#include "Object.h"

Object::Object(Model* model, vec3f pos, quatf rot) 
: model(model)
, p0(pos)
, r0(rot)
, mass(1)
{}

void Object::AddForce(vec3f force) {
  p2 += force / mass;
}

void Object::StepPhysics(Fixed step) {
  std::cout << step << " " << p2 << " " << p1 << " " << p0 << "\n";
  p1 += p2 * step;
  r1 += r2 * step;
  std::cout << step << " " << p2 << " " << p1 << " " << p0 << "\n";
  p0 += p1 * step;
  r0 += r1 * step;
  std::cout << step << " " << p2 << " " << p1 << " " << p0 << "\n";
  p2 = vec3f();
  r2 = quatf();
}
