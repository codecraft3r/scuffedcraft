#include "world/chunk_generator.h"

namespace cppcraft::world {

ChunkGenerator::ChunkGenerator() {
    noise = FastNoise::New<FastNoise::Perlin>();
}

void ChunkGenerator::generateChunk(Chunk& chunk) {
    int chunkX = chunk.getChunkPosition()[0];
    int chunkZ = chunk.getChunkPosition()[1];

    // Example implementation of chunk generation using Perlin noise
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            float height = noise->GenSingle2D((chunkX * CHUNK_SIZE + x) * 0.1f, (chunkZ * CHUNK_SIZE + z) * 0.1f, WORLD_SEED);
            int intHeight = static_cast<int>((height + 1.0f) * 0.5f * CHUNK_HEIGHT);
            
            // Fill with stone up to the height
            for (int y = 0; y < intHeight; ++y) {
                chunk.setBlock(x, y, z, Block(BlockType::STONE, Position(x, y, z)));
            }
            
            // Fill remaining space with air blocks
            for (int y = intHeight; y < CHUNK_HEIGHT; ++y) {
                chunk.setBlock(x, y, z, Block(BlockType::AIR, Position(x, y, z)));
            }
        }
    }
}

} // namespace cppcraft::world