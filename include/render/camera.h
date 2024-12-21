#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cppcraft::render {
    class Camera {
        public:
            Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far);
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();

        private:
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;
            float fov;
            float aspect;
            float near;
            float far;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
    };
}