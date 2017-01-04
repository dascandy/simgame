#pragma once

#include <cstddef>
#include "Scene.h"
#include <string>
#include <memory>
#include <thread>
#include "LockedQueue.h"
#include <functional>
#include <cassert>

class Window {
public:
  Window(const std::string& name, size_t x, size_t y);
  void Close();
  void Do(std::function<void()>&& f);
  void SetScene(std::function<Scene*()> newScene);
  void MainLoop();
  ~Window();
private:
  void* myWindow;
  size_t w, h;
  LockedQueue<std::function<void()>> pendingTasks;
public:
  std::shared_ptr<Scene> scene;
};

