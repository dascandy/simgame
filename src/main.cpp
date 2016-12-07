#include "Material.h"
#include "Model.h"
#include "Scene.h"
#include "Window.h"
#include <atomic>
#include <GLAD/glad.h>
#include "ShaderProgram.h"

#ifdef _MSC_VER
#include "windows.h"

int main();

int __stdcall WinMain(HINSTANCE, HINSTANCE, char*, int) {
  return main();
}
#endif

const char* vs = 
"#version 330\n"
"in vec3 in_loc;\n"
"in vec3 in_nrm;\n"
"void main() {\n"
"   gl_Position = vec4(in_loc, 1);\n"
"}\n"
;
const char* fs = 
"#version 330\n"
"void main() {\n"
"   gl_FragColor = vec4(1, 0, 1, 0);\n"
"}\n"
;

const char*invars[] = {
  "in_loc",
  "in_nrm",
  nullptr
};

int main() {
  class MyScene : public Scene {
  public:
    MyScene() 
    : sp(new ShaderProgram(__FILE__, vs, fs, invars))
    {
    }
    void Update(size_t frameno) override {
      printf("update %d\n", (int)frameno++);
      if (frameno == 300) Window::Instance().Close();
    }
    void Render() override {
      glClearColor(0, 1, 1, 0);
      glClear(GL_COLOR_BUFFER_BIT);
    }
    void Resize(size_t x, size_t y) override {
      // TODO
    }
    std::unique_ptr<ShaderProgram> sp;
  };
  Window win("TestWindow", 640, 480, []{ return new MyScene(); });
  win.MainLoop();
}

