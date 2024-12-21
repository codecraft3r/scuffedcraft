#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace cppcraft::render {

class PrimitiveShapes {
public:
    static std::vector<glm::vec3> createCubeVertices(float size);
    static std::vector<glm::vec3> createCubeColors(const glm::vec3& color);
    static std::vector<glm::vec3> createPyramidVertices(float baseSize, float height);
    static std::vector<glm::vec3> createPyramidColors(const glm::vec3& color);
};

}