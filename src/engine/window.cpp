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
      initialised_{false},
      currentFrame_{0.0f},
      lastFrame_{0.0f},
      deltaTime_{0.0f} {
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
    glfwSetWindowUserPointer(window_, this);
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
#ifdef USE_IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 410");
#endif
  }
}

void Window::onMouse(float xpos, float ypos) {
  if (mouseHandler_) {
    mouseHandler_(xpos, ypos);
  }
}
void Window::setMouseHandler(std::function<void(float, float)> mouseHandler) {
  mouseHandler_ = mouseHandler;
  glfwSetCursorPosCallback(
      window_, [](GLFWwindow* window, double xpos, double ypos) {
        auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        self->onMouse(xpos, ypos);
      });
}
void Window::setInputHandler(
    std::function<void(CameraMovement, float)> inputHandler) {
  inputHandler_ = inputHandler;
}
void Window::onInput(GLFWwindow* window) {
  if (inputHandler_) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
    currentFrame_ = glfwGetTime();
    deltaTime_ = currentFrame_ - lastFrame_;
    lastFrame_ = currentFrame_;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      inputHandler_(CameraMovement::FORWARD, deltaTime_);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      inputHandler_(CameraMovement::BACKWARD, deltaTime_);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      inputHandler_(CameraMovement::LEFT, deltaTime_);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      inputHandler_(CameraMovement::RIGHT, deltaTime_);
  }
}
bool Window::isInitialised() { return initialised_; }
bool Window::shouldClose() { return glfwWindowShouldClose(window_); }
void Window::loop(std::function<void(void)> func) {
  while (!shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    onInput(window_);
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