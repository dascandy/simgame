#include "Material.h"
#include "Model.h"
#include "Scene.h"
#include "Window.h"
#include <GLAD/glad.h>
#include <direct.h>

int main() {
  _chdir("C:\\Users\\pebi\\git\\simgame");
  class MyScene : public Scene {
  public:
    void Update(size_t frameno) override {
      printf("update %d\n", frameno++);
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
  Window* win = new Window("TestWindow", 640, 480, myScene);
  Sleep(5000);
}

