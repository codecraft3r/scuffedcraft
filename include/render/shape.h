#pragma once
#include "glm/glm.hpp"
#include <vector>

namespace cppcraft::render {

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

class Shape {
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    void setupShape();

public:
    Shape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Shape();
    void render();
};

}