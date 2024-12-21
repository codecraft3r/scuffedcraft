#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "render/camera.h"
#include "render/shader.h"
#include "render/shape.h"
#include "render/primitives.h"
#include "input.h"
namespace cppcraft {
    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    int main() {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }
        glfwSetErrorCallback(error_callback);

        GLFWwindow* window = glfwCreateWindow(800, 600, "scuffedcraft", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize OpenGL" << std::endl;
            glfwTerminate();
            return -1;
        }

        glViewport(0, 0, 800, 600);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        render::Camera camera = render::Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        glfwSetWindowUserPointer(window, &camera);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        
        unsigned int shaderProgram = render::createShaderProgram("./shaders/vertex.glsl", "./shaders/fragment.glsl");

        render::Shape cube = render::PrimitiveShapes::createCube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        float lastFrame = 0.0f;
        while (!glfwWindowShouldClose(window)) {
            // move camera
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            cppcraft::processInput(window, camera, deltaTime);

            // render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = camera.getProjectionMatrix();
            glUseProgram(shaderProgram);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

            // render cube
            cube.render();


            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }
}

int main() {
    return cppcraft::main();
}