//
// Created by levi on 2023.07.18..
//

#include "InputHandler.h"
#include "Camera.h"

InputHandler::InputHandler(Camera* camerap, float cameraSensitivityp) {
	camera = camerap;
    cameraSensitivity = cameraSensitivityp;
}

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods, float deltaTime)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_W:
               	camera->ProcessKeyboard(Camera::FORWARD, deltaTime);
                break;
            case GLFW_KEY_S:
                camera->ProcessKeyboard(Camera::BACKWARD, deltaTime);
                break;
            case GLFW_KEY_A:
                camera->ProcessKeyboard(Camera::LEFT, deltaTime);
                break;
            case GLFW_KEY_D:
                camera->ProcessKeyboard(Camera::RIGHT, deltaTime);
                break;
            case GLFW_KEY_SPACE:
                camera->ProcessKeyboard(Camera::UP, deltaTime);
                break;
            case GLFW_KEY_LEFT_SHIFT:
                camera->ProcessKeyboard(Camera::DOWN, deltaTime);
                break;
            default:
                break;
        }
    }
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        leftMouseButtonPressed = true;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        leftMouseButtonPressed = false;
}

void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse) // this bool variable is initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    xoffset *= cameraSensitivity;
    yoffset *= cameraSensitivity;

    if (leftMouseButtonPressed)
    {
        camera->ProcessMouseMovement(xoffset, yoffset);
    }
}
