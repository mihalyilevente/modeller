
#define STB_IMAGE_IMPLEMENTATION
#include "external/GLAD/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "calss/Window.h"
#include "calss/Buffer.h"
#include "calss/Shader.h"
#include "calss/Camera.h"
#include "ext/matrix_clip_space.hpp"
#include "calss/ObjLoader.h"
#include "calss/InputHandler.h"
#include "calss/Texture.h"

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

    std::cout << "camera.getFov: ";
    std::cout << camera.getFOV();
    std::cout << "\n";
    std::cout << "camera.getYaw: ";
    std::cout << camera.getYaw();
    std::cout << "\n";
    std::cout << "camera.getPitch: ";
    std::cout << camera.getPitch();
    std::cout << "\n";
    std::cout << "camera.getPosition: ";
    std::cout << camera.getPosition()[0];
    std::cout << ",";
    std::cout << camera.getPosition()[1];
    std::cout << ",";
    std::cout << camera.getPosition()[2];
    std::cout << ",";
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   inputHandler.mouse_callback(window,xpos, ypos);
}

void unpackData(
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& texCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::ivec3>& faces,
        const std::vector<glm::ivec3>& texIndices,
        const std::vector<glm::ivec3>& normIndices,
        std::vector<glm::vec3>& unpackedVertices,
        std::vector<glm::vec2>& unpackedTexCoords,
        std::vector<glm::vec3>& unpackedNormals
) {
    size_t facesSize = faces.size();
    for (size_t i = 0; i < facesSize; i++) {
        for (int j = 0; j < 3; j++) {
            unpackedVertices.push_back(vertices[faces[i][j] - 1]);
            unpackedNormals.push_back(normals[normIndices[i][j] - 1]);
        }
    }

    size_t texIndicesSize = texIndices.size();
    for (size_t i = 0; i < texIndicesSize; i++) {
        for (int j = 0; j < 2; j++) {
            unpackedTexCoords.push_back(texCoords[texIndices[i][j] - 1]);
        }
    }
}
void logData(const std::vector<glm::vec3>& vertices,
             const std::vector<glm::vec2>& texCoords,
             const std::vector<glm::vec3>& normals,
             const std::vector<glm::ivec3>& faces,
             const std::vector<glm::ivec3>& texIndices,
             const std::vector<glm::ivec3>& normIndices) {

    std::cout << "Vertices:\n";
    for (const auto& v : vertices) {
        std::cout << v.x << ", " << v.y << ", " << v.z << "\n";
    }

    std::cout << "Texture Coordinates:\n";
    for (const auto& tc : texCoords) {
        std::cout << tc.x << ", " << tc.y << "\n";
    }

    std::cout << "Normals:\n";
    for (const auto& n : normals) {
        std::cout << n.x << ", " << n.y << ", " << n.z << "\n";
    }

    std::cout << "Faces:\n";
    for (const auto& f : faces) {
        std::cout << f.x << ", " << f.y << ", " << f.z << "\n";
    }

    std::cout << "Texture Indices:\n";
    for (const auto& ti : texIndices) {
        std::cout << ti.x << ", " << ti.y << ", " << ti.z << "\n";
    }

    std::cout << "Normal Indices:\n";
    for (const auto& ni : normIndices) {
        std::cout << ni.x << ", " << ni.y << ", " << ni.z << "\n";
    }
}



int main() {
    try {
        ObjLoader objLoader;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        std::vector<glm::ivec3> faces;
        std::vector<glm::ivec3> texIndices;
        std::vector<glm::ivec3> normIndices;
        objLoader.loadObj("/home/levi/CLionProjects/modeller/objects/Gear.obj", vertices, texCoords, normals, faces, texIndices,normIndices);

        //logData(vertices, texCoords, normals, faces, texIndices, normIndices);
        std::vector<glm::vec3> unpackedVertices;
        std::vector<glm::vec2> unpackedTexCoords;
        std::vector<glm::vec3> unpackedNormals;
        unpackData(vertices, texCoords, normals, faces, texIndices, normIndices, unpackedVertices, unpackedTexCoords, unpackedNormals);
        Window window(windowWidth, windowHeight, "Hello World");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            return -1;
        }
        //glEnable(GL_DEPTH_TEST); // Enable depth testing
        //glEnable(GL_CULL_FACE);  // Enable backface culling
        //glCullFace(GL_FRONT);

        Buffer buffer(vertices, texCoords, normals, faces);
        Shader shader("/home/levi/CLionProjects/modeller/shaders/vertex_shader.glsl",
                      "/home/levi/CLionProjects/modeller/shaders/fragment_shader.glsl");
        Texture texture0("/home/levi/CLionProjects/modeller/textures/Gear_1_BaseColor.png");
        Texture texture1("/home/levi/CLionProjects/modeller/textures/Gear_1_Diffuse.png");
        Texture texture2("/home/levi/CLionProjects/modeller/textures/Gear_1_Glossiness.png");
        Texture texture3("/home/levi/CLionProjects/modeller/textures/Gear_1_Metallic.png");
        Texture texture4("/home/levi/CLionProjects/modeller/textures/Gear_1_Normal.png");
        Texture texture5("/home/levi/CLionProjects/modeller/textures/Gear_1_Roughness.png");
        Texture texture6("/home/levi/CLionProjects/modeller/textures/Gear_1_Specular.png");

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use the shader program
            texture0.bind(0);
            texture1.bind(3);
            texture2.bind(2);
            texture3.bind(3);
            texture4.bind(4);
            texture5.bind(5);
            texture6.bind(6);
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
            texture0.unbind(0);
            texture1.unbind(1);
            texture2.unbind(2);
            texture3.unbind(3);
            texture4.unbind(4);
            texture5.unbind(5);
            texture6.unbind(6);
            buffer.unbind();
            window.swapBuffers();
        }
    }catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

