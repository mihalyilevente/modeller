#include "external/GLAD/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "calss/Window.h"
#include "calss/Buffer.h"
#include "calss/Shader.h"
#include "calss/Camera.h"
#include "ext/matrix_clip_space.hpp"

float triangle[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

float cube[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
};

// global variables for timing to calculate deltaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// global variable for the camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.02f);

// Callback for keyboard input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_W:
                camera.ProcessKeyboard(Camera::FORWARD, deltaTime);
                break;
            case GLFW_KEY_S:
                camera.ProcessKeyboard(Camera::BACKWARD, deltaTime);
                break;
            case GLFW_KEY_A:
                camera.ProcessKeyboard(Camera::LEFT, deltaTime);
                break;
            case GLFW_KEY_D:
                camera.ProcessKeyboard(Camera::RIGHT, deltaTime);
                break;
            case GLFW_KEY_SPACE:
                camera.ProcessKeyboard(Camera::UP, deltaTime);
                break;
            case GLFW_KEY_LEFT_SHIFT:
                camera.ProcessKeyboard(Camera::DOWN, deltaTime);
                break;
            default:
                break;
        }
    }
}

int main() {
    Window window(640, 480, "Hello World");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }
    // Set the window's user pointer to the camera object
    glfwSetWindowUserPointer(window.getWindow(), &camera);

    // Set the key callback function
    glfwSetKeyCallback(window.getWindow(), key_callback);

    Buffer buffer(triangle, sizeof(triangle));
    Shader shader("/home/levi/CLionProjects/modeller/shaders/vertex_shader.glsl", "/home/levi/CLionProjects/modeller/shaders/fragment_shader.glsl");

    while (!window.shouldClose()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        shader.use();

        // Update the camera transformation
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        buffer.bind();

        // Draw the triangles
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swapBuffers();
    }

    return 0;
}
