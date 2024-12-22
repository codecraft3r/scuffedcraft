#pragma once
#include "glm/glm.hpp"
#include <vector>

namespace cppcraft::render {

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
};

class Shape {
private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void setupShape();

public:
    Shape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Shape();
    void render() const;

    const std::vector<Vertex>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }
};

}