//
// Created by levi on 2023.07.22..
//

#ifndef OBJECT_H
#define OBJECT_H


#include "lib.h"
#include "Buffer.h"
#include "ObjLoader.h"
#include "Shader.h"
#include "Texture.h"

class Object {
public:
    Object(const std::string& objFilePath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& texturePath);

    void moveVertically(int n);

	Buffer* getBuffer();
    Shader* getShader();
    Texture* getTexture();

    void draw();

private:
    ObjLoader* objLoader;
    Buffer* buffer;
    Shader* shader;
    Texture* texture;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;
    std::vector<glm::ivec3> texIndices;
    std::vector<glm::ivec3> normIndices;

};

#endif //OBJECT_H
