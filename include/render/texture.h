#pragma once
#include <glad/glad.h>
#include <string>

namespace cppcraft::render {

class Texture {
public:
    Texture();
    Texture(const std::string& path);
    ~Texture();
    void bind();
private:
    GLuint glTexture;
};

} // namespace cppcraft::render