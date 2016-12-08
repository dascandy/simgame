#pragma once

#include <cstddef>

class Scene {
public:
  virtual ~Scene() {}
  virtual void Update(size_t frameno) = 0;
  virtual void Render() = 0;
  virtual void Resize(size_t x, size_t y) = 0;
};

