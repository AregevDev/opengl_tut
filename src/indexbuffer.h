#ifndef OPENGL_TUT_INDEXBUFFER_H
#define OPENGL_TUT_INDEXBUFFER_H

class IndexBuffer {
private:
    unsigned int rendererID{};
    unsigned int count;
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount();
};

#endif //OPENGL_TUT_INDEXBUFFER_H
