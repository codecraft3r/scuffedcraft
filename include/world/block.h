#pragma once
#include <vector>
#include "world/position.h"
#include "render/texture.h"
namespace cppcraft::world
{

enum class BlockType
{
    AIR,
    DIRT,
    GRASS,
    STONE,
    WOOD,
    LEAVES,
    FALLBACK
};

const std::string GetBlockTypeName(BlockType type);

class Block
{
private:
    BlockType blockType;
    Position position;
public:
    Block();
    Block(BlockType type, Position position);
    BlockType GetType() const;
    Position GetPosition() const;
    ~Block();
};

}