#include "renderable.h"
void Renderable::activate() { shader_->activate(); }
void Renderable::deactivate() { shader_->deactivate(); }
void Renderable::render(
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures) {
  for (auto mesh : meshes_) {
    auto material_id = mesh->getMaterialId();
    if (textures.find(material_id) != textures.end()) {
      textures[material_id]->activate(0);
    }
    mesh->activate();
    mesh->draw();
  }
}
void Renderable::test() {
  for (int i = 0; i < meshes_.size(); ++i) {
    meshes_[i]->activate();
    shader_->activate();
    shader_->loadUniform("texture1", 0);
    shader_->validate();
  }
}

const int Renderable::create() {
  meshes_.push_back(std::make_shared<Mesh>());
  return meshes_.size() - 1;
}
void Renderable::attach(int id, std::vector<float> coordinates, int location,
                        int size) {
  if (id < meshes_.size()) {
    meshes_[id]->attachVertexBuffer(coordinates, location, size);
  }
}
void Renderable::attach(int id, std::vector<float> coordinates, int location,
                        int size, std::string texture_name) {
  if (id < meshes_.size()) {
    meshes_[id]->attachVertexBuffer(coordinates, location, size);
    meshes_[id]->attachMaterialId(texture_name);
  }
}

void Renderable::attach(std::shared_ptr<Shader> shader) { shader_ = shader; }
