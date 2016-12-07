#pragma once

#include <cstddef>
#include "Scene.h"
#include <string>
#include <memory>
#include <thread>

class Window {
public:
  Window(const std::string& name, size_t x, size_t y, std::shared_ptr<Scene> scene);
  void Close();
  ~Window();
private:
  std::thread myThread;
  void* myWindow;
};

