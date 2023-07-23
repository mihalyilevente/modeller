#ifndef TEXTURE_H
#define TEXTURE_H

#include "lib.h"

class Texture {
public:
    Texture(const std::string& filepath);

    void bind(unsigned int unit) const;

    void unbind(unsigned int unit) const;
private:

    GLuint id;
};

#endif // TEXTURE_H
