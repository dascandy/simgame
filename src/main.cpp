#include "Material.h"
#include "Model.h"
#include "Scene.h"
#include "Window.h"
#include <atomic>
#include <GLAD/glad.h>

#ifdef _MSC_VER
#include "windows.h"

int main();

int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int) {
  return main();
}
#endif

int main() {
  class MyScene2 : public Scene {
  public:
    void Update(size_t frameno) override {
      printf("update %d\n", (int)frameno++);
      if (frameno == 300) Window::Instance().Close();
    }
    void Render() override {
      glClearColor(1, 0, 0, 0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
    void Resize(size_t x, size_t y) override {
      // TODO
    }
  };
  class MyScene : public Scene {
  public:
    void Update(size_t frameno) override {
      printf("update %d\n", (int)frameno++);
      if (frameno == 150) Window::Instance().SetScene(std::make_shared<MyScene2>());
      if (frameno == 151) abort();
    }
    void Render() override {
      glClearColor(1, 0, 1, 0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
    void Resize(size_t x, size_t y) override {
      // TODO
    }
  };
  std::shared_ptr<Scene> myScene = std::make_shared<MyScene>();
  Window win("TestWindow", 640, 480, myScene);
  win.MainLoop();
}

