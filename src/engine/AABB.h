#include <glm/glm.hpp>
#include "movable.h"
#include "renderable.h"

class AABB : Movable, Renderable {
 public:
  AABB();
  AABB(glm::vec3 position, glm::mat4 scale);
  AABB(glm::vec3 min, glm::vec3 max);
  void update();
  void render();

 private:
  glm::vec3 min_;
  glm::vec3 max_;
};
