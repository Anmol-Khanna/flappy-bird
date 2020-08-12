#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class Camera {
 public:
  Camera(const glm::mat4 projection, const float currentXPos,
         const float currentYPos,
         const glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         const float yaw = YAW, const float pitch = PITCH);
  glm::mat4 getViewMatrix();
  glm::mat4 getTransform();
  void processKeyboard(const CameraMovement direction, const float deltaTime);

  void processMouseMovement(float xpos, float ypos, bool constrainPitch = true);

 private:
  void updateCameraVectors();
  float currentXPos_;
  float currentYPos_;
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 worldUp_;
  glm::mat4 projection_;
  float yaw_;
  float pitch_;
  float movementSpeed_;
  float mouseSensitivity_;
  float zoom_;
};
#endif
