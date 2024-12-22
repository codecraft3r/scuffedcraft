#include "world/chunk.h"
#include <iostream>

namespace cppcraft::world {

Chunk::Chunk(int16_t chunkX, int16_t chunkZ) : chunkX(chunkX), chunkZ(chunkZ) {
    blocks = new Block[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT];
}

Chunk::~Chunk() {
    delete[] blocks;
}

Block& Chunk::getBlock(int x, int y, int z) {
    if (x < 0 || x > CHUNK_SIZE || y < 0 || y > CHUNK_HEIGHT || z < 0 || z > CHUNK_SIZE) {
        static Block nullBlock(BlockType::AIR, Position(-INT16_MAX,-INT16_MAX,-INT16_MAX));
        //std::cerr << "Attempted block access at " << x << ", " << y << ", " << z << " was out of chunk bounds" << std::endl;
        return nullBlock;
    }
    return blocks[x + CHUNK_SIZE * (z + CHUNK_SIZE * y)];
}

std::array<int16_t, 2> Chunk::getChunkPosition() const {
    return {chunkX, chunkZ};
}

void Chunk::setBlock(int x, int y, int z, const Block& block) {
    if (x < 0 || x > CHUNK_SIZE || y < 0 || y > CHUNK_HEIGHT || z < 0 || z > CHUNK_SIZE) {
        std::cerr << "Attempted block set at " << x << ", " << y << ", " << z << " was out of chunk bounds" << std::endl;
        return;
    }
    blocks[x + CHUNK_SIZE * (z + CHUNK_SIZE * y)] = block;
}

int Chunk::getHighestBlockY() {
    for (int y = CHUNK_HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                if (getBlock(x, y, z).GetType() != BlockType::AIR) {
                    return y;
                }
            }
        }
    }
    std::cerr << "No blocks found in chunk, returning 0" << std::endl;
    return 0;
}

}