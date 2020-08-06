#include "renderable.h"

void Renderable::render(
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures,
    glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
  shader_->activate();
  shader_->loadUniform("texture1", 0);
  for (auto mesh : meshes_) {
    auto material_id = mesh->getMaterialId();
    if (textures.find(material_id) != textures.end()) {
      textures[material_id]->activate(0);
    }
    shader_->loadUniform("model", model);
    shader_->loadUniform("view", view);
    shader_->loadUniform("projection", projection);
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
void Renderable::attach(std::vector<float> positions,
                        std::vector<float> normals, std::vector<float> colours,
                        std::vector<float> texture_coordinates,
                        std::string texture_name) {
  auto mesh{std::make_shared<Mesh>()};
  if (positions.size()) {
    mesh->attachVertexBuffer(positions, 0, 3);
  }
  if (normals.size()) {
    mesh->attachVertexBuffer(normals, 1, 3);
  }
  if (colours.size()) {
    mesh->attachVertexBuffer(colours, 2, 3);
  }
  if (texture_coordinates.size()) {
    mesh->attachVertexBuffer(texture_coordinates, 3, 2);
    mesh->attachMaterialId(texture_name);
  }
  meshes_.push_back(mesh);
}

void Renderable::attach(std::shared_ptr<Shader> shader) { shader_ = shader; }