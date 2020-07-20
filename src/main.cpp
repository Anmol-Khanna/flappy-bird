#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "window.h"
#include "shader.h"
#include "mesh.h"
//#include "model.h"

int main() {
  auto window{Window{800, 800, "Flappy Bird", 4, 1}};
  if (!window.isCreated()) {
    return -1;
  }
  // "../../assets/AW101/AW101.FBX"
  window.makeContextCurrent();
  if (!window.isInitialised()) {
    return -1;
  }
  window.loop([&]() {

  });
}
