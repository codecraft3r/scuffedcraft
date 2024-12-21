#include "render/primitives.h"

namespace cppcraft::render {

std::vector<glm::vec3> PrimitiveShapes::createCubeVertices(float size) {
    float halfSize = size / 2.0f;
    return {
        // Front face
        {-halfSize, -halfSize,  halfSize},
        { halfSize, -halfSize,  halfSize},
        { halfSize,  halfSize,  halfSize},
        {-halfSize,  halfSize,  halfSize},
        // Back face
        {-halfSize, -halfSize, -halfSize},
        { halfSize, -halfSize, -halfSize},
        { halfSize,  halfSize, -halfSize},
        {-halfSize,  halfSize, -halfSize},
        // Left face
        {-halfSize, -halfSize, -halfSize},
        {-halfSize, -halfSize,  halfSize},
        {-halfSize,  halfSize,  halfSize},
        {-halfSize,  halfSize, -halfSize},
        // Right face
        { halfSize, -halfSize, -halfSize},
        { halfSize, -halfSize,  halfSize},
        { halfSize,  halfSize,  halfSize},
        { halfSize,  halfSize, -halfSize},
        // Top face
        {-halfSize,  halfSize, -halfSize},
        {-halfSize,  halfSize,  halfSize},
        { halfSize,  halfSize,  halfSize},
        { halfSize,  halfSize, -halfSize},
        // Bottom face
        {-halfSize, -halfSize, -halfSize},
        {-halfSize, -halfSize,  halfSize},
        { halfSize, -halfSize,  halfSize},
        { halfSize, -halfSize, -halfSize}
    };
}

std::vector<glm::vec3> PrimitiveShapes::createCubeColors(const glm::vec3& color) {
    return std::vector<glm::vec3>(24, color);
}

std::vector<glm::vec3> PrimitiveShapes::createPyramidVertices(float baseSize, float height) {
    float halfBase = baseSize / 2.0f;
    return {
        // Base
        {-halfBase, 0.0f, -halfBase},
        { halfBase, 0.0f, -halfBase},
        { halfBase, 0.0f,  halfBase},
        {-halfBase, 0.0f,  halfBase},
        // Sides
        {-halfBase, 0.0f, -halfBase},
        { halfBase, 0.0f, -halfBase},
        { 0.0f, height, 0.0f},

        { halfBase, 0.0f, -halfBase},
        { halfBase, 0.0f,  halfBase},
        { 0.0f, height, 0.0f},

        { halfBase, 0.0f,  halfBase},
        {-halfBase, 0.0f,  halfBase},
        { 0.0f, height, 0.0f},

        {-halfBase, 0.0f,  halfBase},
        {-halfBase, 0.0f, -halfBase},
        { 0.0f, height, 0.0f}
    };
}

std::vector<glm::vec3> PrimitiveShapes::createPyramidColors(const glm::vec3& color) {
    return std::vector<glm::vec3>(18, color);
}

}