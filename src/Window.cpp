#include "Window.h"
#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Settings.h"
#include "di.h"
#include <imgui_impl_glfw_gl3.h>

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
  fprintf(stderr, "Error %d: %s\n", error, description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Window* win = (Window*)glfwGetWindowUserPointer(window);
  win->keyCallback(key, scancode, action, mods);
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose((GLFWwindow*)myWindow, GLFW_TRUE);
  } else if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
    DI::Get<Settings>()->debugWindow = !DI::Get<Settings>()->debugWindow;
  } else if (DI::Get<Settings>()->debugWindow) {
    ImGui_ImplGlfwGL3_KeyCallback((GLFWwindow*)myWindow, key, scancode, action, mods);
  } else {
    scene->OnKeypress(key, scancode, action, mods);
  }
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
  ImGui_ImplGlfwGL3_Init((GLFWwindow*)myWindow, false);
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

void Window::DebugWindow() {
  if (DI::Get<Settings>()->debugWindow) {
    ImGui_ImplGlfwGL3_NewFrame();

    ImGui::Checkbox("Bullet debug drawing", &DI::Get<Settings>()->debugBullet);
    ImGui::Checkbox("Bullet debug in front of game", &DI::Get<Settings>()->clearDepthBeforeBulletDebug);

    ImGui::Checkbox("Bullet Wireframe", &DI::Get<Settings>()->bulletWireframe);
    ImGui::Checkbox("Bullet AABB", &DI::Get<Settings>()->bulletAabb);
// These exist, but do nothing tangible.
//    ImGui::Checkbox("Bullet Features text", &DI::Get<Settings>()->bulletFeaturesText);
//    ImGui::Checkbox("Bullet Contact points", &DI::Get<Settings>()->bulletContactPoints);
//    ImGui::Checkbox("Bullet No deactication", &DI::Get<Settings>()->bulletNoDeactivation);
//    ImGui::Checkbox("Bullet No help text", &DI::Get<Settings>()->bulletNoHelpText);
//    ImGui::Checkbox("Bullet Draw text", &DI::Get<Settings>()->bulletDrawText);
//    ImGui::Checkbox("Bullet Profile timings", &DI::Get<Settings>()->bulletProfileTimings);
//    ImGui::Checkbox("Bullet Enable SAT comparison", &DI::Get<Settings>()->bulletEnableSatComparison);
//    ImGui::Checkbox("Bullet Disable bullet LCP", &DI::Get<Settings>()->bulletDisableBulletLCP);
//    ImGui::Checkbox("Bullet Enable CCD", &DI::Get<Settings>()->bulletEnableCCD);
//    ImGui::Checkbox("Bullet Draw constraints", &DI::Get<Settings>()->bulletDrawConstraints);
//    ImGui::Checkbox("Bullet Draw constraint limits", &DI::Get<Settings>()->bulletDrawConstraintLimits);
//    ImGui::Checkbox("Bullet Fast wireframe", &DI::Get<Settings>()->bulletFastWireframe);
//    ImGui::Checkbox("Bullet Draw normals", &DI::Get<Settings>()->bulletDrawNormals);
//    ImGui::Checkbox("Bullet Draw frames", &DI::Get<Settings>()->bulletDrawFrames);

    int display_w, display_h;
    glfwGetFramebufferSize((GLFWwindow*)myWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui::Render();
  }
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

    DebugWindow();

    glfwSwapBuffers((GLFWwindow*)myWindow);
  }
  ImGui_ImplGlfwGL3_Shutdown();
  myWindow = nullptr;
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow((GLFWwindow*)myWindow);
}

Window::~Window() {
}

void Window::Do(std::function<void()> &&f) {
  pendingTasks.push(std::move(f));
}

