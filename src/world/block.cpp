#include "world/block.h"
#include "render/texture_manager.h"

namespace cppcraft::world
{

const std::string GetBlockTypeName(BlockType type)
{
    switch (type)
    {
    case BlockType::AIR:
        return "Air";
    case BlockType::DIRT:
        return "Dirt";
    case BlockType::GRASS:
        return "Grass";
    case BlockType::STONE:
        return "Stone";
    case BlockType::WOOD:
        return "Wood";
    case BlockType::LEAVES:
        return "Leaves";
    case BlockType::FALLBACK:
        return "Fallback";
    default:
        return "Undefined";
    }
}

Block::Block() : blockType(BlockType::AIR), position(Position()) {}

Block::Block(BlockType type, Position position) : blockType(type), position(position) {}

BlockType Block::GetType() const
{
    return blockType;
}

Position Block::GetPosition() const
{
    return position;
}

Block::~Block() {}

}