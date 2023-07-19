#include "external/GLAD/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "calss/Window.h"
#include "calss/Buffer.h"
#include "calss/Shader.h"
#include "calss/Camera.h"
#include "ext/matrix_clip_space.hpp"
#include "calss/ObjLoader.h"
#include "calss/InputHandler.h"

int windowWidth = 1920;
int windowHeight = 1080;

// global variables for timing to calculate deltaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// global variable for the camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.02f);
InputHandler inputHandler(&camera, 1.5f);

// Callback for keyboard input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    inputHandler.key_callback(window,key,scancode,action,mods,deltaTime);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    inputHandler.mouse_button_callback(window,button,action,mods);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   inputHandler.mouse_callback(window,xpos, ypos);
}


int main() {
    try {
        ObjLoader objLoader;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        std::vector<glm::ivec3> faces;
        std::vector<glm::ivec2> texIndices;
        std::vector<glm::ivec3> normIndices;
        objLoader.loadObj("/home/levi/CLionProjects/modeller/objects/Gear.obj", vertices, texCoords, normals, faces, texIndices,normIndices);
        Window window(windowWidth, windowHeight, "Hello World");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            return -1;
        }
        Buffer buffer(vertices, faces);
        Shader shader("/home/levi/CLionProjects/modeller/shaders/vertex_shader.glsl",
                      "/home/levi/CLionProjects/modeller/shaders/fragment_shader.glsl");
        // Set the window's user pointer to the camera object
        glfwSetWindowUserPointer(window.getWindow(), &camera);

        // Set the key callback function
        glfwSetKeyCallback(window.getWindow(), key_callback);
        glfwSetMouseButtonCallback(window.getWindow(), mouse_button_callback);
        glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

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
            shader.setMat4("view", view);
            shader.setMat4("projection", projection);

            buffer.bind();
            // Draw the triangles
            glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
            buffer.unbind();
            window.swapBuffers();
        }
    }catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
