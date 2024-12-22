#include "render/chunk_renderer.h"
#include "render/texture_manager.h"
#include "render/primitives.h"
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

    auto cube = PrimitiveShapes::createCube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Create a unit cube

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                const auto& block = chunk.getBlock(x, y, z);
                if (block.GetType() != cppcraft::world::BlockType::AIR) {
                    // Add vertices and indices for the block
                    for (const auto& vertex : cube.vertices) {
                        vertices.push_back(vertex.position.x + x);
                        vertices.push_back(vertex.position.y + y);
                        vertices.push_back(vertex.position.z + z);
                    }
                    for (const auto& index : cube.indices) {
                        indices.push_back(index + vertices.size() / 3 - cube.vertices.size());
                    }
                }
            }
        }
    }
}

void ChunkRenderer::setupMesh() {
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}


void ChunkRenderer::renderChunk(cppcraft::world::Chunk& chunk) {
    auto& textureManager = TextureManager::getInstance();
    glBindVertexArray(VAO);
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                const auto& block = chunk.getBlock(x, y, z);
                textureManager.getTexture(block.GetType())->bind();
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }
    glBindVertexArray(0);
}

} // namespace cppcraft::render