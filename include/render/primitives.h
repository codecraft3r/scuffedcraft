#pragma once
#include <vector>
#include "render/shape.h"
#include <glm/glm.hpp>

namespace cppcraft::render {

class PrimitiveShapes {
public:
    static Shape createCube(float size, const glm::vec3& color);
    static Shape createPyramid(float baseSize, float height, const glm::vec3& color);
};

}
