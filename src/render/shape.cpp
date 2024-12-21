#include "render/shape.h"

namespace cppcraft::render {
    Shape::Shape(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors) {
        this->vertices = vertices;
        this->colors = colors;
    }

    void Shape::render() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glColorPointer(3, GL_FLOAT, 0, &colors[0]);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
}