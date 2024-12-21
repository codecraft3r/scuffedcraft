#pragma once
#include "world/chunk.h"
#include "FastNoise/FastNoise.h"

#define WORLD_SEED 88443322

namespace cppcraft::world {

class ChunkGenerator {
public:
    ChunkGenerator();
    void generateChunk(Chunk& chunk);

private:
    FastNoise::SmartNode<FastNoise::Perlin> noise; // Perlin noise generator
};

} // namespace cppcraft::world