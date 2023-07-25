//
// Created by levi on 2023.07.22..
//

#ifndef OBJECT_H
#define OBJECT_H


#include "lib.h"
#include "Window.h"
#include "Camera.h"
#include "ObjLoader.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"

class Object {
public:
    Object(const std::string& objFilePath, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& texturePath);

    void draw(Window* window, Camera* camera);

    void translate(const glm::vec3 &vec);
    void rotate(float angle, const glm::vec3 &axis);
    void scale(const glm::vec3 &vec);

    Buffer* getBuffer();
    Shader* getShader();
    Texture* getTexture();

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
    glm::mat4 model;

    void drawTriangles();

};

#endif //OBJECT_H
