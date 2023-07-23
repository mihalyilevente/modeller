#ifndef BUFFER_H
#define BUFFER_H

#include "lib.h"

class Buffer {
public:
    Buffer(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &texCoords,
           const std::vector<glm::vec3> &normals, const std::vector<glm::ivec3> &faces);

    void bind() ;
    void unbind() ;
    ~Buffer();

private:
    unsigned int VAO{}, VBO{}, EBO{}, TBO{}, NBO{};

    void setupVBO(const std::vector<glm::vec3> &vertices);

    void setupTBO(const std::vector<glm::vec2> &texCoords);

    void setupNBO(const std::vector<glm::vec3> &normals);

    void setupEBO(const std::vector<glm::ivec3> &faces);

};

#endif  // BUFFER_H
