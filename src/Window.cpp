#include "Window.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

Window* Window::staticWindow;

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

Window::Window(const std::string& name, size_t x, size_t y, std::shared_ptr<Scene> newScene)
: scene(newScene)
{
  static GlfwInit init;
  staticWindow = this;
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  myWindow = glfwCreateWindow((int)x, (int)y, name.c_str(), nullptr, nullptr);
  if (!myWindow) {
    throw std::runtime_error("Cannot create window");
  }
}

void Window::Close() {
  glfwSetWindowShouldClose((GLFWwindow*)myWindow, GLFW_TRUE);
}

void Window::SetScene(std::shared_ptr<Scene> newScene) {
  Do([newScene, this]{ scene = newScene; });
}

void Window::MainLoop() {
  glfwMakeContextCurrent((GLFWwindow*)myWindow);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSetKeyCallback((GLFWwindow*)myWindow, key_callback);
  glfwSwapInterval(1);
  uint64_t startTime = uint64_t(glfwGetTime() * 60);
  uint64_t timeCounter = startTime;
  while (!glfwWindowShouldClose((GLFWwindow*)myWindow)) {
    glfwPollEvents();
    {
      std::vector<std::function<void()>> pending;
      pendingTasks.pop_all(pending);
      for (auto& p : pending) {
        p();
      }
    }
    int width, height;
    glfwGetFramebufferSize((GLFWwindow*)myWindow, &width, &height);
    glViewport(0, 0, width, height);
    uint64_t currentTime = uint64_t(glfwGetTime() * 60);
    while (timeCounter != currentTime) {
      timeCounter++;
      scene->Update(timeCounter - startTime);
    }
    scene->Render();

    glfwSwapBuffers((GLFWwindow*)myWindow);
  }
  myWindow = nullptr;
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow((GLFWwindow*)myWindow);
}

Window::~Window() {
  staticWindow = nullptr;
}

void Window::Do(std::function<void()> &&f) {
  pendingTasks.push(std::move(f));
}

