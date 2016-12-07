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
  Window(const std::string& name, size_t x, size_t y, std::function<Scene*()> scene);
  void Close();
  void Do(std::function<void()>&& f);
  void SetScene(std::function<Scene*()> newScene);
  void MainLoop();
  ~Window();
  static Window& Instance() { assert(staticWindow); return *staticWindow; }
private:
  static Window* staticWindow;
  void* myWindow;
  LockedQueue<std::function<void()>> pendingTasks;
  std::shared_ptr<Scene> scene;
};

