#include "Camera.h"
#include "ext/matrix_transform.hpp"

// Constructor
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          MovementSpeed(SPEED),
          MouseSensitivity(SENSITIVITY),
          FOV(FOV)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt matrix
glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system
void Camera::ProcessKeyboard(Movement direction, float deltaTime)
{
    float velocity = Speed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UP)
        Position += WorldUp * velocity;
    if (direction == DOWN)
        Position -= WorldUp * velocity;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

float Camera::getFOV() const {
    return FOV;
}

void Camera::setMovementSpeed(float speed) {
    MovementSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity) {
    MouseSensitivity = sensitivity;
}


