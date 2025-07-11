#pragma once
#include "world/block.h"

#define CHUNK_SIZE 16 // 0-16 inclusive
#define CHUNK_HEIGHT 255 // 0-255 inclusive

namespace cppcraft::world {

class Chunk {
public:
    Chunk(int16_t chunkX, int16_t chunkZ);
    ~Chunk();

    std::array<int16_t, 2> getChunkPosition() const;
    Block& getBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, const Block& block);
    int getHighestBlockY();

private:
    Block* blocks;
    int16_t chunkX;
    int16_t chunkZ;
};

}