#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <cstdlib>

class Window {
public:
    Window(int width, int height, const char* title);
    bool shouldClose() const;
    void swapBuffers();
    ~Window();

    GLFWwindow *getWindow();

private:
    GLFWwindow* window;
};

#endif  // WINDOW_H
