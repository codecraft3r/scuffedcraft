#include "input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cppcraft {
    float lastX = 400, lastY = 300;
    bool firstMouse = true;
    bool cursorLocked = false;

    void processInput(GLFWwindow* window, render::Camera& camera, float deltaTime) {
        bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            cursorLocked = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        camera.processKeyboard(deltaTime, forward, backward, left, right);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        if (!cursorLocked) {
            return;
        }
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        render::Camera* camera = static_cast<render::Camera*>(glfwGetWindowUserPointer(window));
        camera->processMouseMovement(xoffset, yoffset);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            cursorLocked = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}