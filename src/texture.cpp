#include "texture.h"
#include "renderer.h"

#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string &filepath) : filepath(filepath), width(0), height(0), bpp(0) {
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpp, 4);

    GL_CALL(glGenTextures(1, &rendererID))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, rendererID))

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer))
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &rendererID))
    if (localBuffer)
        stbi_image_free(localBuffer);
}

void Texture::bind(unsigned int slot) const {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, rendererID))
}

void Texture::unbind() const {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
}
