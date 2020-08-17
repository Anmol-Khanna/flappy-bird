#include "AABB.h"

// constructs a unit cube about the origin
AABB::AABB() {
  min_ = glm::vec3(-0.5f, -0.5f, -0.5f);
  max_ = glm::vec3(+0.5f, +0.5f, +0.5f);
}

// constructs an AABB of given scale, about given position
AABB::AABB(glm::vec3 position, glm::mat4 scale) {
  // @TODO(anmol): make this actually do somthing
  min_ = glm::vec3(0.0f, 0.0f, 0.0f);
  max_ = glm::vec3(0.0f, 0.0f, 0.0f);
}

// creates AABB from min and max points
AABB::AABB(glm::vec3 min, glm::vec3 max) {
  // @TODO(anmol): check that min is always < max, if not, swap them
  min_ = min;
  max_ = max;
}

// sets position to the position of the linked Object
void AABB::update() {
  // @TODO(anmol): update
  return;
}

// draws the AABB
void AABB::render() {
  std::vector<float> vertices = {
      // front face
      max_[0],min_[1],min_[2],
      max_[0],min_[1],max_[2],
      max_[0],max_[1],max_[2],
      max_[0],max_[1],min_[2],
      // back face
      min_[0],min_[1],min_[2],
      min_[0],min_[1],max_[2],
      min_[0],max_[1],max_[2],
      min_[0],max_[1],min_[2],
      // left face
      min_[0],min_[1],min_[2],
      max_[0],min_[1],min_[2],
      max_[0],max_[1],min_[2],
      min_[0],max_[1],min_[2],
      // right face
      min_[0],min_[1],max_[2],
      max_[0],min_[1],max_[2],
      max_[0],max_[1],max_[2],
      min_[0],max_[1],max_[2],
      // top face
      min_[0],max_[1],min_[2],
      max_[0],max_[1],min_[2],
      max_[0],max_[1],max_[2],
      min_[0],max_[1],max_[2],
      // bottom face
      min_[0],min_[1],min_[2],
      max_[0],min_[1],min_[2],
      max_[0],min_[1],max_[2],
      min_[0],min_[1],max_[2],
  };

  // create and bind VAO, VBO, pull in shaders, glDrawArrays()
}