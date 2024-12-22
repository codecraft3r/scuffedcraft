#pragma once
#include "render/texture.h"
#include "world/block.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace cppcraft::render {

class TextureManager {
public:
    static TextureManager& getInstance();
    void loadTexture(const cppcraft::world::BlockType blockType, const std::string& path);
    std::shared_ptr<Texture> getTexture(const cppcraft::world::BlockType blockType);

private:
    TextureManager() = default;
    std::unordered_map<cppcraft::world::BlockType, std::shared_ptr<Texture>> textures;
};

} // namespace cppcraft::render