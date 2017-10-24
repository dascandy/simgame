#pragma once

#include "glm.h"
#include <cstdint>

struct Drawcall {
  glm::mat4 mvp;
  uint32_t offset, length;
};


