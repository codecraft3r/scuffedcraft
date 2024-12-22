#include "render/chunk_renderer.h"
#include "world/chunk.h"
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
    auto cube = PrimitveShape::createCube(1.0f, glm::vec3(1.0f, 0.0f, 0.0f)); // Create a unit cube

    // Check visibility of each face
    bool renderFront = (z == 0 || chunk.getBlock(x, y, z - 1).GetType() == cppcraft::world::BlockType::AIR);
    bool renderBack = (z == CHUNK_SIZE || chunk.getBlock(x, y, z + 1).GetType() == cppcraft::world::BlockType::AIR);
    bool renderLeft = (x == 0 || chunk.getBlock(x - 1, y, z).GetType() == cppcraft::world::BlockType::AIR);
    bool renderRight = (x == CHUNK_SIZE || chunk.getBlock(x + 1, y, z).GetType() == cppcraft::world::BlockType::AIR);
    bool renderTop = (y == CHUNK_HEIGHT || chunk.getBlock(x, y + 1, z).GetType() == cppcraft::world::BlockType::AIR);
    bool renderBottom = (y == 0 || chunk.getBlock(x, y - 1, z).GetType() == cppcraft::world::BlockType::AIR);

    if (renderFront || renderBack || renderLeft || renderRight || renderTop || renderBottom) {
        GLuint texture = TextureManager::getInstance().getTexture(block.GetType())->getGlTexture();
        for (const auto& vertex : cube.getVertices()) {
            textureBatches[texture].vertices.push_back(vertex.position.x + x);
            textureBatches[texture].vertices.push_back(vertex.position.y + y);
            textureBatches[texture].vertices.push_back(vertex.position.z + z);
        }

        if (renderFront) {
            addFaceIndices(cube.frontFaceIndices, texture);
        }
        if (renderBack) {
            addFaceIndices(cube.backFaceIndices, texture);
        }
        if (renderLeft) {
            addFaceIndices(cube.leftFaceIndices, texture);
        }
        if (renderRight) {
            addFaceIndices(cube.rightFaceIndices, texture);
        }
        if (renderTop) {
            addFaceIndices(cube.topFaceIndices, texture);
        }
        if (renderBottom) {
            addFaceIndices(cube.bottomFaceIndices, texture);
        }
    }
}

void ChunkRenderer::addFaceIndices(const std::vector<GLuint>& faceIndices, GLuint texture) {
    for (const auto& index : faceIndices) {
        textureBatches[texture].indices.push_back(index + textureBatches[texture].vertices.size() / 3 - 8); // Adjust index based on the number of vertices
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void ChunkRenderer::flushDrawBatch() {
    glBindVertexArray(VAO);

    for (const auto& [texture, batch] : textureBatches) {
        std::cout << "Rendering texture: " << texture << std::endl;
        if (batch.vertices.empty() || batch.indices.empty()) {
            continue;
        }      
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, batch.vertices.size() * sizeof(float), batch.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch.indices.size() * sizeof(GLuint), batch.indices.data(), GL_STATIC_DRAW);

        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, batch.indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    textureBatches.clear();
}

void ChunkRenderer::renderChunk(cppcraft::world::Chunk& chunk, Camera& camera) {
    generateMesh(chunk);
    flushDrawBatch();
}

} // namespace cppcraft::render