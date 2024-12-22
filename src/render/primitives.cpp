#include "render/primitives.h"

namespace cppcraft::render {

PrimitiveShape PrimitiveShape::createCube(float size, const glm::vec3& color) {
    float halfSize = size / 2.0f;
    std::vector<Vertex> vertices = {
        // Front face
        {{-halfSize, -halfSize,  halfSize}, color, {0.0f, 0.0f}},
        {{ halfSize, -halfSize,  halfSize}, color, {1.0f, 0.0f}},
        {{ halfSize,  halfSize,  halfSize}, color, {1.0f, 1.0f}},
        {{-halfSize,  halfSize,  halfSize}, color, {0.0f, 1.0f}},
        // Back face
        {{-halfSize, -halfSize, -halfSize}, color, {1.0f, 0.0f}},
        {{ halfSize, -halfSize, -halfSize}, color, {0.0f, 0.0f}},
        {{ halfSize,  halfSize, -halfSize}, color, {0.0f, 1.0f}},
        {{-halfSize,  halfSize, -halfSize}, color, {1.0f, 1.0f}},
        // Left face
        {{-halfSize, -halfSize, -halfSize}, color, {0.0f, 0.0f}},
        {{-halfSize, -halfSize,  halfSize}, color, {1.0f, 0.0f}},
        {{-halfSize,  halfSize,  halfSize}, color, {1.0f, 1.0f}},
        {{-halfSize,  halfSize, -halfSize}, color, {0.0f, 1.0f}},
        // Right face
        {{ halfSize, -halfSize, -halfSize}, color, {1.0f, 0.0f}},
        {{ halfSize, -halfSize,  halfSize}, color, {0.0f, 0.0f}},
        {{ halfSize,  halfSize,  halfSize}, color, {0.0f, 1.0f}},
        {{ halfSize,  halfSize, -halfSize}, color, {1.0f, 1.0f}},
        // Top face
        {{-halfSize,  halfSize, -halfSize}, color, {0.0f, 1.0f}},
        {{-halfSize,  halfSize,  halfSize}, color, {0.0f, 0.0f}},
        {{ halfSize,  halfSize,  halfSize}, color, {1.0f, 0.0f}},
        {{ halfSize,  halfSize, -halfSize}, color, {1.0f, 1.0f}},
        // Bottom face
        {{-halfSize, -halfSize, -halfSize}, color, {1.0f, 1.0f}},
        {{-halfSize, -halfSize,  halfSize}, color, {1.0f, 0.0f}},
        {{ halfSize, -halfSize,  halfSize}, color, {0.0f, 0.0f}},
        {{ halfSize, -halfSize, -halfSize}, color, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9, 10, 10, 11, 8,
        // Right face
        12, 13, 14, 14, 15, 12,
        // Top face
        16, 17, 18, 18, 19, 16,
        // Bottom face
        20, 21, 22, 22, 23, 20
    };

    return PrimitiveShape(vertices, indices);
}

PrimitiveShape PrimitiveShape::createPyramid(float baseSize, float height, const glm::vec3& color) {
    float halfBase = baseSize / 2.0f;
    std::vector<Vertex> vertices = {
        // Base
        {{-halfBase, 0.0f, -halfBase}, color},
        {{ halfBase, 0.0f, -halfBase}, color},
        {{ halfBase, 0.0f,  halfBase}, color},
        {{-halfBase, 0.0f,  halfBase}, color},
        // Sides
        {{-halfBase, 0.0f, -halfBase}, color},
        {{ halfBase, 0.0f, -halfBase}, color},
        {{ 0.0f, height, 0.0f}, color},

        {{ halfBase, 0.0f, -halfBase}, color},
        {{ halfBase, 0.0f,  halfBase}, color},
        {{ 0.0f, height, 0.0f}, color},

        {{ halfBase, 0.0f,  halfBase}, color},
        {{-halfBase, 0.0f,  halfBase}, color},
        {{ 0.0f, height, 0.0f}, color},

        {{-halfBase, 0.0f,  halfBase}, color},
        {{-halfBase, 0.0f, -halfBase}, color},
        {{ 0.0f, height, 0.0f}, color}
    };

    std::vector<unsigned int> indices = {
        // Base
        0, 1, 2, 2, 3, 0,
        // Sides
        4, 5, 6,
        7, 8, 9,
        10, 11, 12,
        13, 14, 15
    };

    return PrimitiveShape(vertices, indices);
}

// Define face indices for each face of the cube
const std::vector<GLuint> PrimitiveShape::frontFaceIndices = {0, 1, 2, 2, 3, 0};
const std::vector<GLuint> PrimitiveShape::backFaceIndices = {4, 5, 6, 6, 7, 4};
const std::vector<GLuint> PrimitiveShape::leftFaceIndices = {8, 9, 10, 10, 11, 8};
const std::vector<GLuint> PrimitiveShape::rightFaceIndices = {12, 13, 14, 14, 15, 12};
const std::vector<GLuint> PrimitiveShape::topFaceIndices = {16, 17, 18, 18, 19, 16};
const std::vector<GLuint> PrimitiveShape::bottomFaceIndices = {20, 21, 22, 22, 23, 20};

} // namespace cppcraft::render