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
    std::cout << "key_callback was called\n";

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            case GLFW_KEY_W:
                camera.ProcessKeyboard(Camera::FORWARD, deltaTime);
                std::cout << "GLFW_KEY_W key was pressed\n";
                break;
            case GLFW_KEY_S:
                camera.ProcessKeyboard(Camera::BACKWARD, deltaTime);
                std::cout << "GLFW_KEY_S key was pressed\n";
                break;
            case GLFW_KEY_A:
                camera.ProcessKeyboard(Camera::LEFT, deltaTime);
                std::cout << "GLFW_KEY_A key was pressed\n";
                break;
            case GLFW_KEY_D:
                camera.ProcessKeyboard(Camera::RIGHT, deltaTime);
                std::cout << "GLFW_KEY_D key was pressed\n";
                break;
            case GLFW_KEY_SPACE:
                camera.ProcessKeyboard(Camera::UP, deltaTime);
                std::cout << "GLFW_KEY_SPACE key was pressed\n";
                break;
            case GLFW_KEY_LEFT_SHIFT:
                camera.ProcessKeyboard(Camera::DOWN, deltaTime);
                std::cout << "GLFW_KEY_LEFT_SHIFT key was pressed\n";
                break;
            default:
                break;
        }
    }
}

bool firstMouse = true;
float lastX = 0;
float lastY = 0;


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

int main() {
    try {
        Window window(640, 480, "Hello World");

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            return -1;
        }
        // Set the window's user pointer to the camera object
        glfwSetWindowUserPointer(window.getWindow(), &camera);

        // Set the key callback function
        glfwSetKeyCallback(window.getWindow(), key_callback);
        glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
        glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        Buffer buffer(cube, sizeof(cube));
        Shader shader("/home/levi/CLionProjects/modeller/shaders/vertex_shader.glsl",
                      "/home/levi/CLionProjects/modeller/shaders/fragment_shader.glsl");

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
            float aspectRatio = window.getWidth() / (float) window.getHeight();
            glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), aspectRatio, 0.1f, 100.0f);
            std::cout << "view: ";
            std::cout << view.length();
            std::cout << "\n";
            std::cout << "projection: ";
            std::cout << projection.length();
            std::cout << "\n";
            std::cout << "camera.getFov: ";
            std::cout << camera.getFOV();
            std::cout << "\n";
            std::cout << "camera.getPosition: ";
            std::cout << camera.getPosition()[0];
            std::cout << ",";
            std::cout << camera.getPosition()[1];
            std::cout << ",";
            std::cout << camera.getPosition()[2];
            std::cout << "\n";
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);

            buffer.bind();

            // Draw the triangles
            glDrawArrays(GL_TRIANGLES, 0, 36);

            window.swapBuffers();
        }
    }catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
