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

        void Camera::updateFrustumPlanes() {
        glm::mat4 vpMatrix = projectionMatrix * getViewMatrix();
        frustumPlanes[0] = glm::vec4(vpMatrix[0][3] + vpMatrix[0][0], vpMatrix[1][3] + vpMatrix[1][0], vpMatrix[2][3] + vpMatrix[2][0], vpMatrix[3][3] + vpMatrix[3][0]); // Left
        frustumPlanes[1] = glm::vec4(vpMatrix[0][3] - vpMatrix[0][0], vpMatrix[1][3] - vpMatrix[1][0], vpMatrix[2][3] - vpMatrix[2][0], vpMatrix[3][3] - vpMatrix[3][0]); // Right
        frustumPlanes[2] = glm::vec4(vpMatrix[0][3] + vpMatrix[0][1], vpMatrix[1][3] + vpMatrix[1][1], vpMatrix[2][3] + vpMatrix[2][1], vpMatrix[3][3] + vpMatrix[3][1]); // Bottom
        frustumPlanes[3] = glm::vec4(vpMatrix[0][3] - vpMatrix[0][1], vpMatrix[1][3] - vpMatrix[1][1], vpMatrix[2][3] - vpMatrix[2][1], vpMatrix[3][3] - vpMatrix[3][1]); // Top
        frustumPlanes[4] = glm::vec4(vpMatrix[0][3] + vpMatrix[0][2], vpMatrix[1][3] + vpMatrix[1][2], vpMatrix[2][3] + vpMatrix[2][2], vpMatrix[3][3] + vpMatrix[3][2]); // Near
        frustumPlanes[5] = glm::vec4(vpMatrix[0][3] - vpMatrix[0][2], vpMatrix[1][3] - vpMatrix[1][2], vpMatrix[2][3] - vpMatrix[2][2], vpMatrix[3][3] - vpMatrix[3][2]); // Far

        for (int i = 0; i < 6; i++) {
            float length = glm::length(glm::vec3(frustumPlanes[i]));
            frustumPlanes[i] /= length;
        }
    }

    bool Camera::isInFrustum(const glm::vec3& point) {
        for (int i = 0; i < 6; i++) {
            if (glm::dot(glm::vec3(frustumPlanes[i]), point) + frustumPlanes[i].w <= 0) {
                return false;
            }
        }
        return true;
    }
}