#include "movable.h"

Movable::Movable(glm::vec3 position, glm::mat4 scale, glm::mat4 translation,
                 glm::mat4 rotation)
    : position_{position},
      scale_{scale},
      translation_{translation},
      rotation_{rotation} {}

void Movable::setPosition(glm::vec3 newPosition) { position_ = newPosition; }
const glm::vec3& Movable::getPosition() { return position_; }
void Movable::setScale(glm::mat4 newScale) { scale_ = newScale; }
const glm::mat4& Movable::getScale() { return scale_; }
void Movable::setTranslation(glm::mat4 newTranslation) {
  translation_ = newTranslation;
}
const glm::mat4& Movable::getTranslation() { return translation_; }
void Movable::setRotation(glm::mat4 newRotation) { rotation_ = newRotation; }
const glm::mat4& Movable::getRotation() { return rotation_; }
const glm::mat4 Movable::getTransform() {
  return translation_ * rotation_ * scale_;
}