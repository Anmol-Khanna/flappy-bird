#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

class Window {
 public:
  Window(const int width, const int height, const std::string title,
         const int contextVersionMajor, const int contextVersionMinor);
  bool isCreated();
  void makeContextCurrent();
  bool isInitialised();
  bool shouldClose();
  void loop(std::function<void(void)> func);

 private:
  int width_;
  int height_;
  std::string title_;
  GLFWwindow* window_;
  int contextVersionMinor_;
  int contextVersionMajor_;
  bool created_;
  bool initialised_;
};

#endif