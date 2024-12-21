#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cppcraft {

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    GLFWwindow* getGLFWwindow() const;

private:
    GLFWwindow* window;
};

}