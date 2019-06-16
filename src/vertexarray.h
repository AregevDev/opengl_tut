#ifndef OPENGL_TUT_VERTEXARRAY_H
#define OPENGL_TUT_VERTEXARRAY_H

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray {
private:
    unsigned int rendererID{};
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout);
    void bind() const;
    void unbind() const;
};

#endif //OPENGL_TUT_VERTEXARRAY_H
