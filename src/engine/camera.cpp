#include "camera.h"

Camera::Camera(const glm::mat4 projection, const float currentXPos,
               const float currentYPos, const glm::vec3 position,
               const glm::vec3 up, const float yaw, const float pitch)
    : projection_{projection},
      currentXPos_{currentXPos},
      currentYPos_{currentYPos},
      position_{position},
      front_(glm::vec3(0.0f, 0.0f, -1.0f)),
      up_{up},
      worldUp_{up},
      yaw_{yaw},
      pitch_{pitch},
      movementSpeed_(SPEED),
      mouseSensitivity_(SENSITIVITY),
      zoom_(ZOOM) {
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position_, position_ + front_, up_);
}

glm::mat4 Camera::getTransform() {
  return projection_ * glm::lookAt(position_, position_ + front_, up_);
}

void Camera::processKeyboard(const CameraMovement direction,
                             const float deltaTime) {
  float velocity = movementSpeed_ * deltaTime;
  if (direction == CameraMovement::FORWARD)
    position_ += front_ * velocity;
  else if (direction == CameraMovement::BACKWARD)
    position_ -= front_ * velocity;
  else if (direction == CameraMovement::LEFT)
    position_ -= right_ * velocity;
  else if (direction == CameraMovement::RIGHT)
    position_ += right_ * velocity;
}

void Camera::processMouseMovement(float xpos, float ypos, bool constrainPitch) {
  auto xoffset = xpos - currentXPos_;
  auto yoffset = ypos - currentYPos_;
  currentXPos_ = xpos;
  currentYPos_ = ypos;

  xoffset *= mouseSensitivity_;
  yoffset *= mouseSensitivity_;

  yaw_ += xoffset;
  pitch_ += yoffset;

  if (constrainPitch) {
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
  }

  updateCameraVectors();
}

void Camera::updateCameraVectors() {
  // calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front.y = sin(glm::radians(pitch_));
  front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_ = glm::normalize(front);
  right_ = glm::normalize(glm::cross(front_, worldUp_));
  up_ = glm::normalize(glm::cross(right_, front_));
}