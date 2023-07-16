#include "Window.h"

Window::Window(int width, int height, const char* title) {
    this->height = height;
    this->width = width;
    if (!glfwInit()) {
        // Initialization failed
        exit(EXIT_FAILURE);
    }

    // Create the window and its OpenGL context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Window::getWindow() {
    return window;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}
