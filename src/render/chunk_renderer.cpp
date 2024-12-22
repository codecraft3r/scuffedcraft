#include "render/chunk_renderer.h"
#include "world/chunk.h"
#include "render/texture_manager.h"
#include <iostream>

namespace cppcraft::render {

ChunkRenderer::ChunkRenderer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

ChunkRenderer::~ChunkRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void ChunkRenderer::initializeChunk(cppcraft::world::Chunk& chunk) {
    generateMesh(chunk);
    setupMesh();
}

void ChunkRenderer::generateMesh(cppcraft::world::Chunk& chunk) {
    vertices.clear();
    indices.clear();

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                const auto& block = chunk.getBlock(x, y, z);
                if (block.GetType() != cppcraft::world::BlockType::AIR) {
                    addBlockMesh(chunk, block, x, y, z);
                }
            }
        }
    }
}

void ChunkRenderer::addBlockMesh(cppcraft::world::Chunk& chunk, const cppcraft::world::Block& block, int x, int y, int z) {
    auto cube = PrimitiveShape::createCube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    GLuint texture = TextureManager::getInstance().getTexture(block.GetType())->getGlTexture();

    // Helper function to check face visibility
    auto isFaceVisible = [&](int dx, int dy, int dz) {
        return chunk.getBlock(x + dx, y + dy, z + dz).GetType() == cppcraft::world::BlockType::AIR;
    };

    // Check visibility of each face
    if (z == 0 || isFaceVisible(0, 0, -1)) addVerticesForFace(cube, PrimitiveShape::frontFaceIndices, x, y, z, texture);
    if (z == CHUNK_SIZE - 1 || isFaceVisible(0, 0, 1)) addVerticesForFace(cube, PrimitiveShape::backFaceIndices, x, y, z, texture);
    if (x == 0 || isFaceVisible(-1, 0, 0)) addVerticesForFace(cube, PrimitiveShape::leftFaceIndices, x, y, z, texture);
    if (x == CHUNK_SIZE - 1 || isFaceVisible(1, 0, 0)) addVerticesForFace(cube, PrimitiveShape::rightFaceIndices, x, y, z, texture);
    if (y == CHUNK_HEIGHT - 1 || isFaceVisible(0, 1, 0)) addVerticesForFace(cube, PrimitiveShape::topFaceIndices, x, y, z, texture);
    if (y == 0 || isFaceVisible(0, -1, 0)) addVerticesForFace(cube, PrimitiveShape::bottomFaceIndices, x, y, z, texture);
}

void ChunkRenderer::addVerticesForFace(const PrimitiveShape& shape, const std::vector<GLuint>& faceIndices, int x, int y, int z, GLuint texture) {
    auto& batch = textureBatches[texture];

    for (const auto& index : faceIndices) {
        glm::vec3 vertex = shape.getVertices().at(index).position;
        vertex += glm::vec3(x, y, z);
        batch.vertices.push_back(vertex.x);
        batch.vertices.push_back(vertex.y);
        batch.vertices.push_back(vertex.z);
    }

    GLuint offset = batch.vertices.size() / 3 - faceIndices.size();
    for (const auto& index : faceIndices) {
        batch.indices.push_back(offset + index);
    }
}

void ChunkRenderer::setupMesh() {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
}

void ChunkRenderer::flushDrawBatch(GLuint shaderProgram) {
    glBindVertexArray(VAO);

    GLuint instanceVBO;
    glGenBuffers(1, &instanceVBO);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    for (unsigned int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4) * i));
        glVertexAttribDivisor(3 + i, 1);
    }

    for (const auto& [texture, batch] : textureBatches) {
        if (batch.vertices.empty() || batch.indices.empty()) continue;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, batch.vertices.size() * sizeof(float), batch.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch.indices.size() * sizeof(GLuint), batch.indices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, batch.instanceMatrices.size() * sizeof(glm::mat4), batch.instanceMatrices.data(), GL_STATIC_DRAW);

        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElementsInstanced(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, 0, batch.instanceMatrices.size());
    }

    glDeleteBuffers(1, &instanceVBO);
    glBindVertexArray(0);
    textureBatches.clear();
}

void ChunkRenderer::renderChunk(cppcraft::world::Chunk& chunk, Camera& camera, GLuint shaderProgram) {
    generateMesh(chunk);
    flushDrawBatch(shaderProgram);
}

} // namespace cppcraft::render