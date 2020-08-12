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
#include "object.h"

int main() {
  constexpr int SCR_WIDTH = 800, SCR_HEIGHT = 800;
  Camera camera{
      glm::perspective(glm::radians(45.0f),
                       (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f),
      (float)SCR_WIDTH / 2.0f, (float)SCR_HEIGHT / 2.0f};
  Object player{};
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
  std::string vertexCode = getShaderCode("src/player/helicopter.vs");
  std::string fragmentCode = getShaderCode("src/player/helicopter.fs");
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

  float maxExtent = 0.5f * (bmax[0] - bmin[0]);
  if (maxExtent < 0.5f * (bmax[1] - bmin[1])) {
    maxExtent = 0.5f * (bmax[1] - bmin[1]);
  }
  if (maxExtent < 0.5f * (bmax[2] - bmin[2])) {
    maxExtent = 0.5f * (bmax[2] - bmin[2]);
  }
  for (int i = 0; i < positions.size(); ++i) {
    player.attach({positions[i], 0, 3}, {normals[i], 1, 3}, {colours[i], 2, 3},
                  {texture_coordinates[i], 3, 2}, texture_names[i]);
  }
  Shader shader{vertexCode, fragmentCode};
  player.attach(std::make_shared<Shader>(shader));
  player.Movable::setScale(glm::scale(
      glm::mat4(1.0f),
      glm::vec3(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent)));
  float angle = 0.0f;
  window.loop([&]() {
    angle += 1.0f;
    player.Movable::setRotation(
        glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0)));
    player.render(textures, camera.getTransform());
  });
}
