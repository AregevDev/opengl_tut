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

    [[nodiscard]] std::vector<VertexBufferElement> getElements() const;
    [[nodiscard]] unsigned int getStride() const;
};

#endif //OPENGL_TUT_VERTEXBUFFERLAYOUT_H
