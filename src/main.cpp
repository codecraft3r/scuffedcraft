#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "render/camera.h"
#include "render/shader.h"
#include "render/chunk_renderer.h"
#include "render/shader_locations.h"
#include "render/texture_manager.h"
#include "render/texture_locations.h"


#include "world/chunk.h"
#include "world/chunk_generator.h"

#include "window.h"
#include "input.h"

namespace cppcraft {
    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    void initGLFWOrExit(void glfw_error_callback(int, const char*)) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }
        glfwSetErrorCallback(glfw_error_callback);
    }

    void initOpenGLOrExit() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize OpenGL context" << std::endl;
            exit(-1);
        }
    }

    int main() {
        initGLFWOrExit(error_callback);
        Window window = Window(800, 600, "CppCraft");

        glViewport(0, 0, 800, 600);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        auto& textureManager = cppcraft::render::TextureManager::getInstance();
        textureManager.loadTexture(world::BlockType::STONE, STONE_TEXTURE_PATH);
        textureManager.loadTexture(world::BlockType::FALLBACK, FALLBACK_TEXTURE_PATH);
        
        unsigned int shaderProgram = render::createShaderProgram(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

        world::Chunk chunk(0, 0);
        world::ChunkGenerator chunkGenerator;

        std::cout << "Generating chunk" << std::endl;
        chunkGenerator.generateChunk(chunk);
        std::cout << "Chunk generated" << std::endl;
        
        render::ChunkRenderer chunkRenderer = render::ChunkRenderer();
        chunkRenderer.initializeChunk(chunk);

        render::Camera camera = render::Camera(glm::vec3(0.0f, chunk.getHighestBlockY() + 1.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        glfwSetWindowUserPointer(window.getGLFWwindow(), &camera);
        glfwSetCursorPosCallback(window.getGLFWwindow(), mouse_callback);
        glfwSetMouseButtonCallback(window.getGLFWwindow(), mouse_button_callback);

        initOpenGLOrExit();
        float lastFrame = 0.0f;
        while (!window.shouldClose()) {
            // move camera
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            cppcraft::processInput(window.getGLFWwindow(), camera, deltaTime);

            // render

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 view = camera.getViewMatrix();
            glm::mat4 projection = camera.getProjectionMatrix();
            glm::mat4 model = glm::mat4(1.0f);
            glUseProgram(shaderProgram);
            
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
           
            chunkRenderer.renderChunk(chunk, camera);


            window.swapBuffers();
            window.pollEvents();
        }
        
        glfwTerminate();
        return 0;
    }
}

int main() {
    return cppcraft::main();
}