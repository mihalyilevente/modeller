
#define STB_IMAGE_IMPLEMENTATION
#include "calss/InputHandler.h"
#include "calss/Object.h"
#include "external/imgui/imgui.h"
#include "external/imgui/backends/imgui_impl_glfw.h"
#include "external/imgui/backends/imgui_impl_opengl3.h"


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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main() {
    try {
        const std::string objFilePath = "/home/levi/CLionProjects/modeller/objects/Gear.obj";
        const std::string vertexShaderPath = "/home/levi/CLionProjects/modeller/shaders/vertex_shader.glsl";
        const std::string fragmentShaderPath = "/home/levi/CLionProjects/modeller/shaders/fragment_shader.glsl";
        const std::string texturePath = "/home/levi/CLionProjects/modeller/textures/Gear_1_BaseColor.png";

        Window window(windowWidth, windowHeight, "Modeller");
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            return -1;
        }
        Object object(objFilePath, vertexShaderPath, fragmentShaderPath, texturePath);
        inputHandler.setObjectInFocus(&object);
        //glEnable(GL_DEPTH_TEST); // Enable depth testing
        //glEnable(GL_CULL_FACE);  // Enable backface culling
        //glCullFace(GL_FRONT);    //Enable frontface culling

        // Set the window's user pointer to the camera object
        glfwSetWindowUserPointer(window.getWindow(), &camera);

        // Set the key callback function
        glfwSetKeyCallback(window.getWindow(), key_callback);
        glfwSetMouseButtonCallback(window.getWindow(), mouse_button_callback);
        glfwSetCursorPosCallback(window.getWindow(), mouse_callback);


        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
        ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        while (!window.shouldClose()) {

            // input
            // -----
            processInput(window.getWindow());

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Rendering ImGui Windows
            ImGui::Begin("Demo window");
            ImGui::Button("Hello!");
            ImGui::End();

            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Draw the triangles
            object.draw(&window, &camera);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            window.swapBuffers();
            glfwPollEvents();
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

    }catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

