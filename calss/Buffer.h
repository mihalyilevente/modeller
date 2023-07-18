#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <vector>
#include "../external/GLM/glm.hpp"

class Buffer {
public:
    Buffer(const std::vector<glm::vec3>& vertices, const std::vector<glm::ivec3>& faces);
    void bind() ;
    void unbind() ;
    ~Buffer();

private:
    unsigned int VAO{}, VBO{}, EBO{};
};

#endif  // BUFFER_H
