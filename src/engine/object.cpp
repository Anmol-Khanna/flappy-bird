#include "object.h"

Object::Object() : objects_{} {}

void Object::attach(
    std::tuple<std::vector<float>, int, int> positions_location_size,
    std::tuple<std::vector<float>, int, int> normals_location_size,
    std::tuple<std::vector<float>, int, int> colours_location_size,
    std::tuple<std::vector<float>, int, int> texture_coordinates_location_size,
    std::string texture_name) {
  Renderable::attach(positions_location_size, normals_location_size,
                     colours_location_size, texture_coordinates_location_size,
                     texture_name);
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
  Renderable::set("model", Movable::getTransform());
  Renderable::set("viewProjection", transform);
  Renderable::set("texture1", 0);
  Renderable::render(textures);
}