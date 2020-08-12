#include "renderable.h"

void Renderable::render(
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures) {
  shader_->activate();
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
void Renderable::attach(
    std::tuple<std::vector<float>, int, int> positions_location_size,
    std::tuple<std::vector<float>, int, int> normals_location_size,
    std::tuple<std::vector<float>, int, int> colours_location_size,
    std::tuple<std::vector<float>, int, int> texture_coordinates_location_size,
    std::string texture_name) {
  auto mesh{std::make_shared<Mesh>()};
  auto positions = std::get<0>(positions_location_size);
  auto location = std::get<1>(positions_location_size);
  auto size = std::get<2>(positions_location_size);
  if (positions.size()) {
    mesh->attachVertexBuffer(positions, location, size);
  }
  auto normals = std::get<0>(normals_location_size);
  location = std::get<1>(normals_location_size);
  size = std::get<2>(normals_location_size);
  if (normals.size()) {
    mesh->attachVertexBuffer(normals, location, size);
  }
  auto colours = std::get<0>(colours_location_size);
  location = std::get<1>(colours_location_size);
  size = std::get<2>(colours_location_size);
  if (colours.size()) {
    mesh->attachVertexBuffer(colours, location, size);
  }
  auto texture_coordinates = std::get<0>(texture_coordinates_location_size);
  location = std::get<1>(texture_coordinates_location_size);
  size = std::get<2>(texture_coordinates_location_size);
  if (texture_coordinates.size()) {
    mesh->attachVertexBuffer(texture_coordinates, location, size);
    mesh->attachMaterialId(texture_name);
  }
  meshes_.push_back(mesh);
}

void Renderable::attach(std::shared_ptr<Shader> shader) { shader_ = shader; }
