#include "Object.h"

Object::Object(Model* model, glm::vec3 pos, glm::quat rot) 
: model(model)
, pos(pos)
, rot(rot)
{}

