#pragma once

#include <glm.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <memory>
class Model;

class Object {
public:
  Object(std::shared_ptr<Model> model, vec3 pos, quat rot);
  void AddForce(vec3 force);
  vec3 getPosition();
  quat getRotation();
  std::shared_ptr<Model> model;
private:
  btDefaultMotionState motionState;
  btRigidBody rigidBody;
};

