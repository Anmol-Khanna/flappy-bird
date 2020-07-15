#include "window.h"

Window::Window(const int width, const int height, const std::string title,
               const int contextVersionMajor, const int contextVersionMinor)
    : width_{width},
      height_{height},
      title_{title},
      contextVersionMajor_{contextVersionMajor},
      contextVersionMinor_{contextVersionMinor},
      created_{false},
      initialised_{false} {
  if (!glfwInit()) {
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (window_) {
    created_ = true;
  }
}

bool Window::isCreated() { return created_; }
void Window::makeContextCurrent() {
  if (created_) {
    glfwMakeContextCurrent(window_);
    initialised_ = gladLoadGL();
  }
}
bool Window::isInitialised() { return initialised_; }
bool Window::shouldClose() { return glfwWindowShouldClose(window_); }
void Window::loop(std::function<void(void)> func) {
  while (!shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT);
    func();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}