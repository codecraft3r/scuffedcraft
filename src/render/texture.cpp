#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include "render/texture.h"

namespace cppcraft::render {

Texture::Texture() {}

Texture::Texture(const std::string& path) {
    std::cout << "Creating texture from path: " << path << std::endl;
    glGenTextures(1, &glTexture);
    glBindTexture(GL_TEXTURE_2D, glTexture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        std::cout << "Texture created successfully: " << path << " with ID: " << glTexture << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
}

Texture::~Texture() {
    std::cout << "Deleting texture with ID: " << glTexture << std::endl;
    glDeleteTextures(1, &glTexture);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, glTexture);
}

} // namespace cppcraft::render