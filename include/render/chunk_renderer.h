#pragma once
#include "world/chunk.h"
#include <glad/glad.h>
#include <vector>

namespace cppcraft::render {

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();

    void renderChunk(cppcraft::world::Chunk& chunk);
    void initializeChunk(cppcraft::world::Chunk& chunk);

private:
    GLuint VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void setupMesh();
    void generateMesh(cppcraft::world::Chunk& chunk);
};

} // namespace cppcraft::render