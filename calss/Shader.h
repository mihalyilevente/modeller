#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include "ext/matrix_float4x4.hpp"

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat);

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
