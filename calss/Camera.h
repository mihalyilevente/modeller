#ifndef CAMERA_H
#define CAMERA_H

#include "../external/GLM/glm.hpp"
#include <GLFW/glfw3.h>

// Default camera values
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH);


    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::mat4 getViewMatrix() const;
    float getFOV() const;
    glm::vec3 getPosition() ;
    void ProcessKeyboard(Movement direction, float deltaTime);

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true );

private:
    glm::vec3 Position;
    glm::vec3 Up;
    glm::vec3 Front;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Speed;
    float FOV;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;

    void updateCameraVectors();

    void setMovementSpeed(float speed);

    void setMouseSensitivity(float sensitivity);
};

#endif // CAMERA_H
