#ifndef OPENGL_TUT_TEXTURE_H
#define OPENGL_TUT_TEXTURE_H

#include <string>

class Texture {
private:
    unsigned int rendererID{};
    std::string filepath;
    unsigned char *localBuffer;
    int width, height, bpp;
public:
    explicit Texture(const std::string &path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
};

#endif //OPENGL_TUT_TEXTURE_H
