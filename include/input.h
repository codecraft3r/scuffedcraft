#pragma once
#include <GLFW/glfw3.h>
#include "render/camera.h"

namespace cppcraft {
    void processInput(GLFWwindow* window, render::Camera& camera, float deltaTime);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
}