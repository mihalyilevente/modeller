#ifndef TEXTURE_H
#define TEXTURE_H

#include "../external/STB/stb_image.h"
#include "glad/glad.h"
#include <string>
#include <iostream>
#include <GL/gl.h>

class Texture {
public:
    Texture(const std::string& filepath);

    void bind(unsigned int unit) const;

    void unbind(unsigned int unit) const;
private:

    GLuint id;
};

#endif // TEXTURE_H
