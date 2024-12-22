#pragma once
#include <vector>
#include "render/shape.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cppcraft::render {

class PrimitveShape : public Shape {
private:
    PrimitveShape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) : Shape(vertices, indices) {}

    void addFaceIndices(const std::vector<GLuint>& faceIndices);
public:
    static PrimitveShape createCube(float size, const glm::vec3& color);
    static PrimitveShape createPyramid(float baseSize, float height, const glm::vec3& color);

    static const std::vector<GLuint> frontFaceIndices;
    static const std::vector<GLuint> backFaceIndices;
    static const std::vector<GLuint> leftFaceIndices;
    static const std::vector<GLuint> rightFaceIndices;
    static const std::vector<GLuint> topFaceIndices;
    static const std::vector<GLuint> bottomFaceIndices;
};

}