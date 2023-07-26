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
    model = glm::mat4(1.0f);

}

Object::~Object() {
    delete objLoader;
    delete buffer;
    delete shader;
    delete texture;
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

void Object::draw(Window* window, Camera* camera) {

    //Bindings
    buffer->bind();
    shader->use();
    texture->bind(0);

    //bind Shader Params
    float aspectRatio = window->getWidth() / (float) window->getHeight();
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->getFOV()), aspectRatio, 0.1f, 100.0f);
    shader->setMat4("view", view);
    shader->setMat4("model",model);
    shader->setMat4("projection", projection);

    // Draw the triangles
    drawTriangles();

    //Unbindings
    texture->unbind(0);
    buffer->unbind();
}
void Object::drawTriangles() {
    glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, 0);
}


void Object::translate(const glm::vec3& vec) {
    model = glm::translate(model, vec);
}

void Object::rotate(float angle, const glm::vec3& axis) {
    model = glm::rotate(model, glm::radians(angle), axis);
}

void Object::scale(const glm::vec3& vec) {
    model = glm::scale(model, vec);
}
