#ifndef OPENGL_TUT_VERTEXBUFFER_H
#define OPENGL_TUT_VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int rendererID{};
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();


    void bind() const;
    void unbind() const;
};

#endif //OPENGL_TUT_VERTEXBUFFER_H
