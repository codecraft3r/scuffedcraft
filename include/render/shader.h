#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace cppcraft::render {
    
    std::string readFile(const char* filePath);

    unsigned int compileShader(unsigned int type, const char* source);

    unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath);
}