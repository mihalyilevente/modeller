//
// Created by levi on 2023.07.22..
//

#include "Object.h"

Object::Object(const std::string &objFilePath, const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath , const std::string& texturePath) {
    objLoader->loadObj(objFilePath, vertices, texCoords, normals, faces, texIndices,normIndices);
    buffer = new Buffer(vertices, texCoords, normals, faces);
    shader = new Shader(vertexShaderPath, fragmentShaderPath);
    texture = new Texture(texturePath);
}

Buffer* Object::getBuffer() {
    return buffer;
}

Shader *Object::getShader() {
    return shader;
}

Texture *Object::getTexture() {
    return texture;
}

void Object::draw() {
    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
}

void Object::moveVertically(int n) { //does not work
    for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x += n;
		vertices[i].y += n;
		vertices[i].z += n;
    }
}
