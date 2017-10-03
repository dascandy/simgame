#include "Object.h"
#include "Model.h"

Object::Object(std::shared_ptr<Model> model, vec3 pos, quat rot) 
: model(model)
, motionState(btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w), btVector3(pos.x, pos.y, pos.z)))
, rigidBody(model->Create(&motionState))
{}

void Object::AddForce(vec3 force) {
  (void)force;
//  p2 += force / mass;
}

vec3 Object::getPosition() {
  btTransform trans;
  motionState.getWorldTransform(trans);
  return vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

quat Object::getRotation() {
  btTransform trans;
  motionState.getWorldTransform(trans);
  return quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());
}


