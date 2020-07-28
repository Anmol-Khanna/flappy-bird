#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "window.h"
#include "shader.h"
#include "mesh.h"
//#include "model.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
  auto window{Window{800, 800, "Flappy Bird", 4, 1}};
  if (!window.isCreated()) {
    return -1;
  }
  glfwSetKeyCallback(window.getWindow(), key_callback);
  // "../../assets/AW101/AW101.FBX"
  window.makeContextCurrent();
  if (!window.isInitialised()) {
    return -1;
  }

  

  window.loop([&]() {

  });
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  // when a user presses the escape key, we set the WindowShouldClose property
  // to true, closing the application
  
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (key == GLFW_KEY_SPACE) {
    if (action == GLFW_PRESS) {
      std::cout << "JUMP" << std::endl;
    } 
  } else {
      std::cout << key << std::endl;
  }
}
