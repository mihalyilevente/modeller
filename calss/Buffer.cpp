#include <iostream>
#include "Buffer.h"

Buffer::Buffer(
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& texCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::ivec3>& faces) {

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Setup buffers
    setupVBO(vertices);
    setupEBO(faces);

    if (!texCoords.empty()) {
        setupTBO(texCoords);
    }

    if (!normals.empty()) {
        setupNBO(normals);
    }

    glBindVertexArray(0);
}

void Buffer::setupVBO(const std::vector<glm::vec3>& vertices) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Buffer::setupTBO(const std::vector<glm::vec2>& texCoords) {
    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

void Buffer::setupNBO(const std::vector<glm::vec3>& normals) {
    glGenBuffers(1, &NBO);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
}

void Buffer::setupEBO(const std::vector<glm::ivec3>& faces) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(glm::ivec3), &faces[0], GL_STATIC_DRAW);
}

void Buffer::bind() {
    glBindVertexArray(VAO);
}

void Buffer::unbind() {
    glBindVertexArray(0);
}

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &TBO);
    glDeleteBuffers(1, &NBO);
}
