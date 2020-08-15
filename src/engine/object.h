#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <tuple>
#include "mesh.h"
#include "shader.h"
#include "movable.h"
#include "renderable.h"

class Object : public Renderable, public Movable {
 public:
  Object();
  void attach(std::tuple<std::vector<float>, int, int> positions_location_size,
              std::tuple<std::vector<float>, int, int> normals_location_size,
              std::tuple<std::vector<float>, int, int> colours_location_size,
              std::tuple<std::vector<float>, int, int>
                  texture_coordinates_location_size,
              std::string texture_name);
  void attach(std::shared_ptr<Object>);
  void attach(std::shared_ptr<Shader>);
  void render(std::unordered_map<std::string, std::shared_ptr<Texture>>,
              glm::mat4 transform);

 private:
  std::vector<std::shared_ptr<Object>> objects_;
  std::vector<const int> ids_;
};

#endif