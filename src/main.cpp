#include <cstdio>
#include <algorithm>
#include <fstream>
#include <sstream>
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
#include "tinyobjloader_wrapper.h"

int SCR_WIDTH = 800, SCR_HEIGHT = 800;
int main() {
  auto window{Window{SCR_WIDTH, SCR_HEIGHT, "Flappy Bird", 4, 1}};
  if (!window.isCreated()) {
    return -1;
  }
  window.makeContextCurrent();
  if (!window.isInitialised()) {
    return -1;
  }
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open("src/helicopter.vs");
    fShaderFile.open("src/helicopter.fs");
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  float bmin[3], bmax[3];
  std::vector<std::shared_ptr<Mesh>> meshes{};
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
    auto mesh{std::make_shared<Mesh>()};
    mesh->attachVertexBuffer(positions[i], 0, 3);
    if (i < normals.size()) {
      mesh->attachVertexBuffer(normals[i], 1, 3);
    }
    if (i < colours.size()) {
      mesh->attachVertexBuffer(colours[i], 2, 3);
    }
    if (i < texture_coordinates.size()) {
      mesh->attachVertexBuffer(texture_coordinates[i], 3, 2);
      mesh->attachMaterialId(texture_names[i]);
    }
    meshes.push_back(mesh);
  }
  Shader shader{vertexCode, fragmentCode};
  // for (int i=0; i<meshes.size(); ++i){
  //   meshes[i]->activate();
  //   shader.activate();
  //   shader.validate();
  //   shader.loadUniform("texture1", 0);
  // }
  float maxExtent = 0.5f * (bmax[0] - bmin[0]);
  if (maxExtent < 0.5f * (bmax[1] - bmin[1])) {
    maxExtent = 0.5f * (bmax[1] - bmin[1]);
  }
  if (maxExtent < 0.5f * (bmax[2] - bmin[2])) {
    maxExtent = 0.5f * (bmax[2] - bmin[2]);
  }
  shader.activate();
  shader.loadUniform("texture1", 0);
  float angle = 0.0f;
  window.loop([&]() {
    for (auto mesh : meshes) {
      auto material_id = mesh->getMaterialId();
      if (textures.find(material_id) != textures.end()) {
        textures[material_id]->activate(0);
      }
      // create transformations
      glm::mat4 model = glm::mat4(
          1.0f);  // make sure to initialize matrix to identity matrix first
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 projection = glm::mat4(1.0f);
      model = glm::scale(model, glm::vec3(1.0f / maxExtent, 1.0f / maxExtent,
                                          1.0f / maxExtent));
      // view  = glm::translate(view, glm::vec3(-0.5 * (bmax[0] + bmin[0]), -0.5
      // * (bmax[1] + bmin[1]),
      //            -0.5 * (bmax[2] + bmin[2])));
      view = glm::rotate(view, glm::radians(angle), glm::vec3(0, 1, 0));
      angle += 1.0f;
      // projection = glm::perspective(glm::radians(0.0f), (float)SCR_WIDTH /
      // (float)SCR_HEIGHT, 0.1f, 100.0f);
      shader.loadUniform("model", model);
      shader.loadUniform("view", view);
      shader.loadUniform("projection", projection);
      mesh->activate();
      mesh->draw();
    }
  });
}
