#pragma once

#include <cstddef>

class Scene {
public:
  virtual ~Scene() {}
  virtual void OnKeypress(int key, int scancode, int action, int mods) {}
  virtual void Update(size_t frameno) = 0;
  virtual void Render() = 0;
  virtual void Resize(size_t x, size_t y) = 0;
};

