#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <vector>
#include <memory>
#include <tuple>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
class Renderable {
 public:
  void activate();
  void deactivate();
  void render(std::unordered_map<std::string, std::shared_ptr<Texture>>);
  void test();
  const int create();
  void attach(int id, std::vector<float> coordinates, int location, int size);
  void attach(int id, std::vector<float> coordinates, int location, int size,
              std::string texture_name);
  void attach(std::shared_ptr<Shader> shader);
  template <typename T>
  void set(const std::string name, T val) {
    shader_->loadUniform(name, val);
  }

 private:
  std::shared_ptr<Shader> shader_;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  std::vector<std::shared_ptr<Texture>> textures_;
  std::vector<std::shared_ptr<Shader>> shaders_;
};

#endif