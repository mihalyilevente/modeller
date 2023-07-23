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
    Shader(const std::string vertexPath, const std::string fragmentPath);
    void use();
    void setMat4(const std::string &name, const glm::mat4 &mat);
private:

    void setVec3(const std::string &name, const glm::vec3 &vec);

    void setFloat(const std::string &name, float value);

    std::string loadShaderCode(const char *shaderPath);

    unsigned int compileShader(GLenum type, const char *shaderCode, const std::string &typeName);

    void checkCompileErrors(unsigned int shader, const std::string &type);
};

#endif
