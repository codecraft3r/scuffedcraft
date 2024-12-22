#include "render/texture_manager.h"
#include "world/block.h"
#include <stdexcept>
#include <iostream>

namespace cppcraft::render {

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::loadTexture(const cppcraft::world::BlockType blockType, const std::string& path) {
    auto texture = std::make_shared<Texture>(path);
    textures[blockType] = texture;
}

std::shared_ptr<Texture> TextureManager::getTexture(const cppcraft::world::BlockType blockType) {
    auto it = textures.find(blockType);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found for the given block type " + cppcraft::world::GetBlockTypeName(blockType));
    }
    return it->second;
}


} // namespace cppcraft::render