#include "glad/glad.h"
#include "render/camera.h"

namespace cppcraft::render {
    Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspect, float near, float far)
        : position(position), target(target), up(up), fov(fov), aspect(aspect), near(near), far(far) {
        viewMatrix = glm::lookAt(position, target, up);
        projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    glm::mat4 Camera::getViewMatrix() {
        return viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix() {
        return projectionMatrix;
    }
}