#pragma once
#include <glad/glad.h>
#include <string>

namespace cppcraft::render {

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();

    void bind() const;

private:
    GLuint textureID;
};

} // namespace cppcraft::render