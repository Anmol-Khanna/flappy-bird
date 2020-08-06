#include <cstdio>
#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <glad/glad.h>
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "utils.h"
#include "player.h"

int main() {
  constexpr int SCR_WIDTH = 800, SCR_HEIGHT = 800;
  Camera camera{};
  Player player{};
  auto window{Window{SCR_WIDTH, SCR_HEIGHT, "Flappy Bird", 4, 1}};
  if (!window.isCreated()) {
    return -1;
  }
  window.makeContextCurrent();
  if (!window.isInitialised()) {
    return -1;
  }
  window.setMouseHandler(
      [&](float xpos, float ypos) { camera.processMouseMovement(xpos, ypos); });
  window.setInputHandler(
      [&](const CameraMovement direction, const float deltaTime) {
        camera.processKeyboard(direction, deltaTime);
      });
  std::string vertexCode = getShaderCode("src/helicopter.vs");
  std::string fragmentCode = getShaderCode("src/helicopter.fs");
  float bmin[3], bmax[3];
  std::unordered_map<std::string, std::shared_ptr<Texture>> textures{};
  std::vector<std::vector<float>> positions{}, normals{}, colours{},
      texture_coordinates{};
  std::vector<std::string> texture_names{};
  LoadObjAndConvert(
      bmin, bmax, "assets/AW101/AW101.obj",
      [&](std::vector<float> position) { positions.push_back(position); },
      [&](std::vector<float> normal) { normals.push_back(normal); },
      [&](std::vector<float> colour) { colours.push_back(colour); },
      [&](std::vector<float> texture_coordinate, std::string name) {
        texture_coordinates.push_back(texture_coordinate);
        texture_names.push_back(name);
      },
      [&](int width, int height, int channels, unsigned char* image,
          std::string name) {
        auto texture{std::make_shared<Texture>()};
        texture->attachTexture(width, height, channels, image);
        textures.insert({name, texture});
      });

  for (int i = 0; i < positions.size(); ++i) {
    player.Renderable::attach(positions[i], normals[i], colours[i],
                              texture_coordinates[i], texture_names[i]);
  }
  Shader shader{vertexCode, fragmentCode};
  player.Renderable::attach(std::make_shared<Shader>(shader));
  float maxExtent = 0.5f * (bmax[0] - bmin[0]);
  if (maxExtent < 0.5f * (bmax[1] - bmin[1])) {
    maxExtent = 0.5f * (bmax[1] - bmin[1]);
  }
  if (maxExtent < 0.5f * (bmax[2] - bmin[2])) {
    maxExtent = 0.5f * (bmax[2] - bmin[2]);
  }
  float angle = 0.0f;
  window.loop([&]() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::scale(
        model, glm::vec3(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent));
    view = glm::rotate(view, glm::radians(angle), glm::vec3(0, 1, 0));
    // projection = glm::perspective(glm::radians(0.0f), (float)SCR_WIDTH /
    // (float)SCR_HEIGHT, 0.1f, 100.0f);
    angle += 1.0f;
    player.render(textures, model, view, projection);
  });
}
