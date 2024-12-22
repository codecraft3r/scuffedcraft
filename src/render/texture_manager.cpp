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
        std::cerr << "Texture for block type " << cppcraft::world::GetBlockTypeName(blockType) << " not found, using fallback texture" << std::endl;
        return textures[cppcraft::world::BlockType::FALLBACK];
    }
    return it->second;
}


} // namespace cppcraft::render