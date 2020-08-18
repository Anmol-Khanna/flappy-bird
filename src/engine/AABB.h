#include <glm/glm.hpp>
#include "movable.h"
#include "renderable.h"
#include <glm/gtc/type_ptr.hpp>

class AABB : Movable, Renderable {
 public:
  AABB();
  //AABB(glm::vec3 min, glm::vec3 max);
  //void update();
  void render(glm::mat4 transform);

 private:
  glm::vec3 min_;
  glm::vec3 max_;
  float vertices[108]; //72 floats => 24 vertices since each has 3 floats| 108 because need to repeat verts if not using an EBO
  unsigned int AABBShaderProgram;
  unsigned int VAO;
};
