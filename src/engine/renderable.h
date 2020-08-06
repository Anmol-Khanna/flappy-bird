#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <vector>
#include <memory>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
class Renderable {
 public:
  void render(std::unordered_map<std::string, std::shared_ptr<Texture>>,
              glm::mat4 model, glm::mat4 view, glm::mat4 projection);
  void test();
  void attach(std::vector<float> positions, std::vector<float> normals,
              std::vector<float> colours,
              std::vector<float> texture_coordinates, std::string texture_name);
  void attach(std::shared_ptr<Shader> shader);

 private:
  std::shared_ptr<Shader> shader_;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  std::vector<std::shared_ptr<Texture>> textures_;
  std::vector<std::shared_ptr<Shader>> shaders_;
};

#endif