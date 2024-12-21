#include <glad/glad.h>
#include "render/camera.h"

namespace cppcraft::render {
    Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far)
        : position(position), target(target), up(up), worldUp(up), yaw(-90.0f), pitch(0.0f), fov(fov), aspect(aspect), near(near), far(far) {
        updateCameraVectors();
        projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(position, position + target, up);
    }

    glm::mat4 Camera::getProjectionMatrix() {
        return projectionMatrix;
    }

    void Camera::updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        target = glm::normalize(front);
        right = glm::normalize(glm::cross(target, worldUp));
        up = glm::normalize(glm::cross(right, target));
    }

    void Camera::processKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right) {
        float velocity = 2.5f * deltaTime;
        if (forward)
            position += target * velocity;
        if (backward)
            position -= target * velocity;
        if (left)
            position -= this->right * velocity;
        if (right)
            position += this->right * velocity;
    }

    void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (constrainPitch) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
    }
}