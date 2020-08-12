#ifndef MOVABLE_H
#define MOVABLE_H

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Movable {
 public:
  Movable(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
          glm::mat4 scale = glm::mat4(1.0f),
          glm::mat4 translation = glm::mat4(1.0f),
          glm::mat4 rotation = glm::mat4(1.0f));
  void setPosition(glm::vec3 newPosition);
  const glm::vec3& getPosition();
  void setScale(glm::mat4 newScale);
  const glm::mat4& getScale();
  void setTranslation(glm::mat4 newTranslation);
  const glm::mat4& getTranslation();
  void setRotation(glm::mat4 newRotation);
  const glm::mat4& getRotation();
  const glm::mat4 getTransform();

 private:
  glm::vec3 position_;
  glm::mat4 scale_;
  glm::mat4 translation_;
  glm::mat4 rotation_;
};

#endif