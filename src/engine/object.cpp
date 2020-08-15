#include "object.h"

Object::Object() : objects_{}, ids_{} {}

void Object::attach(
    std::tuple<std::vector<float>, int, int> positions_location_size,
    std::tuple<std::vector<float>, int, int> normals_location_size,
    std::tuple<std::vector<float>, int, int> colours_location_size,
    std::tuple<std::vector<float>, int, int> texture_coordinates_location_size,
    std::string texture_name) {
  auto const id = Renderable::create();
  auto positions = std::get<0>(positions_location_size);
  auto location = std::get<1>(positions_location_size);
  auto size = std::get<2>(positions_location_size);
  Renderable::attach(id, positions, location, size);
  auto normals = std::get<0>(normals_location_size);
  location = std::get<1>(normals_location_size);
  size = std::get<2>(normals_location_size);
  Renderable::attach(id, normals, location, size);
  auto colours = std::get<0>(colours_location_size);
  location = std::get<1>(colours_location_size);
  size = std::get<2>(colours_location_size);
  Renderable::attach(id, colours, location, size);
  auto texture_coordinates = std::get<0>(texture_coordinates_location_size);
  location = std::get<1>(texture_coordinates_location_size);
  size = std::get<2>(texture_coordinates_location_size);
  Renderable::attach(id, texture_coordinates, location, size, texture_name);
}
void Object::attach(std::shared_ptr<Object> object) {
  objects_.push_back(object);
}

void Object::attach(std::shared_ptr<Shader> shader) {
  Renderable::attach(shader);
}

void Object::render(
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures,
    glm::mat4 transform) {
  Renderable::activate();
  Renderable::set("model", Movable::getTransform());
  Renderable::set("viewProjection", transform);
  Renderable::set("texture1", 0);
  Renderable::render(textures);
  Renderable::deactivate();
}