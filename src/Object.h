#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Model;

class Object {
public:
  Object(Model* model, glm::vec3 pos, glm::quat rot);
private:
  Model* model;
  glm::vec3 pos;
  glm::quat rot;
};

