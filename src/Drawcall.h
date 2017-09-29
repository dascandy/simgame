#pragma once

#include "glm.h"
#include <cstdint>

struct Drawcall {
  glm::mat4 mvp;
  uint16_t offset, length;
};


