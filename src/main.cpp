#include "Material.h"
#include "Model.h"
#include "Scene.h"
#include "Window.h"
#include <atomic>
#include <GLAD/glad.h>

std::atomic<bool> end(false);

int main() {
  class MyScene : public Scene {
  public:
    void Update(size_t frameno) override {
      printf("update %d\n", (int)frameno++);
      if (frameno == 300) 
        end = true;
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
  win.Close();
//  while (!end) {}
}

