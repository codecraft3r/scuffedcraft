#pragma once
#include "world/chunk.h"
#include "render/camera.h"
#include <glad/glad.h>
#include <vector>

namespace cppcraft::render {

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();

    void renderChunk(cppcraft::world::Chunk& chunk, Camera& camera);
    void initializeChunk(cppcraft::world::Chunk& chunk);

private:
    GLuint VAO, VBO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    struct Batch {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    std::unordered_map<GLuint, Batch> textureBatches;

    void setupMesh();
    void generateMesh(cppcraft::world::Chunk& chunk);
    void addBlockMesh(cppcraft::world::Chunk& chunk, const cppcraft::world::Block& block, int x, int y, int z);
    void addFaceIndices(const std::vector<GLuint>& faceIndices, GLuint texture);
    void flushDrawBatch();
};

} // namespace cppcraft::render