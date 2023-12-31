//
// Created by levi on 2023.07.18..
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H


#include "Camera.h"
#include "Object.h"

class InputHandler {
public:
    InputHandler(Camera* camera, float cameraSensitivity);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods, float deltaTime);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void setObjectInFocus(Object* object);
private:
    bool leftMouseButtonPressed = false;
    bool firstMouse = true;
    double lastX = 0;
    double lastY = 0;
    float cameraSensitivity;
    Camera* camera;
    Object* objectInFocus;
};


#endif //INPUTHANDLER_H
