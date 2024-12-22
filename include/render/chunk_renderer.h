#pragma once
#include "world/chunk.h"
#include "render/camera.h"
#include "render/primitives.h"
#include <glad/glad.h>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

namespace cppcraft::render {

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();

    void renderChunk(cppcraft::world::Chunk& chunk, Camera& camera, GLuint shaderProgram);
    void initializeChunk(cppcraft::world::Chunk& chunk);

private:
    GLuint VAO, VBO, EBO, instanceVBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::mat4> instanceMatrices;

    struct Batch {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<glm::mat4> instanceMatrices;
    };

    std::unordered_map<GLuint, Batch> textureBatches;

    void setupMesh();
    void generateMesh(cppcraft::world::Chunk& chunk);
    void addBlockMesh(cppcraft::world::Chunk& chunk, const cppcraft::world::Block& block, int x, int y, int z);
    void addFaceIndices(const std::vector<GLuint>& faceIndices, GLuint texture);
    void addVerticesForFace(const PrimitiveShape& shape, const std::vector<GLuint>& faceIndices, int x, int y, int z, GLuint texture);
    void flushDrawBatch(GLuint shaderProgram);
};

} // namespace cppcraft::render