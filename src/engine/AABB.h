#include <glm/glm.hpp>
#include "movable.h"
#include "renderable.h"
#include <glm/gtc/type_ptr.hpp>

class AABB : Movable, Renderable {
 public:
  AABB();
  AABB(glm::vec3 min, glm::vec3 max);
  //void update();
  void render(glm::mat4 transform);
  void render(glm::mat4 transform, glm::mat4 model); //@TODO(anmol): find some way for this to be more cleanly set- right now to switch from default 
													 // constructor to this one, I need to change two things in main- the constructor called, and the render method called
													 // when in reality, this render() will ONLY be called with the second constructor. Maybe set a function ptr in the respective 
													 // constructors?

 private:
  glm::vec3 min_;
  glm::vec3 max_;
  float vertices[108]; //72 floats => 24 vertices since each has 3 floats| 108 because need to repeat verts if not using an EBO
  unsigned int AABBShaderProgram;
  unsigned int VAO;
};
