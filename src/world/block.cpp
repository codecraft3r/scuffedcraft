#include "world/block.h"
#include "render/texture_locations.h"

namespace cppcraft::world
{

Block::Block() : blockType(BlockType::AIR), position(Position()) {}

Block::Block(BlockType type, Position position) : blockType(type), position(position) {}

BlockType Block::GetType() const
{
    return blockType;
}

cppcraft::render::Texture Block::GetTexture() {
    switch (blockType) {
        case BlockType::STONE:
            return cppcraft::render::Texture(STONE_TEXTURE_PATH);
        default:
            return cppcraft::render::Texture(FALLBACK_TEXTURE_PATH);
    }
}

Position Block::GetPosition() const
{
    return position;
}

Block::~Block() {}

}