#include "Window.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "glfw3.lib")

class GlfwInit {
public:
  GlfwInit() {
    if (!glfwInit())
      throw std::runtime_error("Cannot init glfw");
  }
  ~GlfwInit() {
    glfwTerminate();
  }
};

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window(const std::string& name, size_t x, size_t y, std::shared_ptr<Scene> scene)
: myThread([this, name, x, y, scene]{
  static GlfwInit init;
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  GLFWwindow* window = glfwCreateWindow((int)x, (int)y, name.c_str(), NULL, NULL);
  if (!window) {
    throw std::runtime_error("Cannot create window");
  }
  myWindow = window;
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSetKeyCallback(window, key_callback);
  glfwSwapInterval(1);
  uint64_t startTime = glfwGetTime() * 60;
  uint64_t timeCounter = startTime;
  while (!glfwWindowShouldClose(window)) {
    // Handle events to run on this thread();
    glfwPollEvents();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    uint64_t currentTime = glfwGetTime() * 60;
    while (timeCounter != currentTime) {
      timeCounter++;
      scene->Update(timeCounter - startTime);
    }
    scene->Render();
    
    glfwSwapBuffers(window);
  }
  glfwMakeContextCurrent(NULL);
  glfwDestroyWindow(window);
})
{
}

Window::~Window() {
  if (myWindow)
    glfwSetWindowShouldClose((GLFWwindow*)myWindow, GLFW_TRUE);
  myThread.join();
}

