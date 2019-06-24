#ifndef OPENGL_TUT_VERTEXBUFFERLAYOUT_H
#define OPENGL_TUT_VERTEXBUFFERLAYOUT_H

#include <iostream>
#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int getSizeOfType(unsigned int type);
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
