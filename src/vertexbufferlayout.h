#ifndef OPENGL_TUT_VERTEXBUFFERLAYOUT_H
#define OPENGL_TUT_VERTEXBUFFERLAYOUT_H

#include <iostream>
#include <vector>
#include <glad/glad.h>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                return 0;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
public:
    VertexBufferLayout() : stride(0) {}

    template<typename T>
    void push(unsigned int count);

    inline const std::vector<VertexBufferElement> getElements() const& { return elements; }
    inline unsigned int getStride() const { return stride; }
};

#endif //OPENGL_TUT_VERTEXBUFFERLAYOUT_H
