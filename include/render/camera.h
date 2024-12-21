#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cppcraft::render {
    class Camera {
        public:
            Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far);
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();
            void updateCameraVectors();
            void processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right);
            void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

        private:
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 worldUp;
            float yaw;
            float pitch;
            float fov;
            float aspect;
            float near;
            float far;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
    };
}