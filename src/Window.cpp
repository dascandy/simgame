#include "Window.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
  Window* win = (Window*)glfwGetWindowUserPointer(window);
  win->scene->OnKeypress(key, scancode, action, mods);
}

Window::Window(const std::string& name, size_t w, size_t h)
: w(w)
, h(h)
{
  static GlfwInit init;
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  myWindow = glfwCreateWindow((int)w, (int)h, name.c_str(), nullptr, nullptr);
  if (!myWindow) {
    throw std::runtime_error("Cannot create window");
  }
  glfwMakeContextCurrent((GLFWwindow*)myWindow);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSetKeyCallback((GLFWwindow*)myWindow, key_callback);
  glfwSetFramebufferSizeCallback((GLFWwindow*)myWindow, [](GLFWwindow* winptr, int x, int y) {
    Window* win = (Window*)glfwGetWindowUserPointer(winptr);
    win->w = x;
    win->h = y;
    win->scene->Resize(x, y);
  });
  glfwSwapInterval(1);
  glfwSetWindowUserPointer((GLFWwindow*)myWindow, this);
}

void Window::Close() {
  glfwSetWindowShouldClose((GLFWwindow*)myWindow, GLFW_TRUE);
}

void Window::SetScene(std::function<Scene*()> newScene) {
  Do([newScene, this]{ 
    scene.reset(newScene()); 
    if (scene) scene->Resize(w, h); 
  });
}

void Window::MainLoop() {
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
    int err = glGetError();
    if (err != 0) {
      std::cerr << err << "\n";
      std::terminate();
    }
    glfwSwapBuffers((GLFWwindow*)myWindow);
  }
  myWindow = nullptr;
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow((GLFWwindow*)myWindow);
}

Window::~Window() {
}

void Window::Do(std::function<void()> &&f) {
  pendingTasks.push(std::move(f));
}

