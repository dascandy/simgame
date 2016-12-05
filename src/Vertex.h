#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
  glm::vec3 pos;
  glm::vec3 normal;
  float padding[2];
};

static_assert(sizeof(Vertex) == 32, "Vertex is not as it should be");

