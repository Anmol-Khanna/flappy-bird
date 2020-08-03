#include "window.h"
#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif

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
#ifdef USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 410");
#endif
  }
}
bool Window::isInitialised() { return initialised_; }
bool Window::shouldClose() { return glfwWindowShouldClose(window_); }
void Window::loop(std::function<void(void)> func) {
  while (!shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT);
#ifdef USE_IMGUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
    func();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}