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

    int getWidth();

    int getHeight();

private:
    GLFWwindow* window;
    int width;
    int height;
};

#endif  // WINDOW_H
