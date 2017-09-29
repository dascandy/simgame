#pragma once

#include <glm.h>

class Vertex {
public:
  glm::vec3 pos;
  glm::vec3 normal;
  uint8_t material;
  uint8_t pad[7];
};

static_assert(sizeof(Vertex) == 32, "Vertex is not as it should be");

