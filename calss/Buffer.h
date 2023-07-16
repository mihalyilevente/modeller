#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

class Buffer {
public:
    Buffer(const void* data, unsigned int size);
    void bind() const;
    void unbind() const;
    ~Buffer();

private:
    unsigned int VAO, VBO;
};

#endif  // BUFFER_H
