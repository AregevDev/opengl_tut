#include "vertexbufferlayout.h"
#include "renderer.h"

template<>
void VertexBufferLayout::push<float>(unsigned int count) {
    elements.push_back({ GL_FLOAT, count, GL_FALSE });
    stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}

unsigned int VertexBufferElement::getSizeOfType(unsigned int type) {
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

std::vector<VertexBufferElement> VertexBufferLayout::getElements() const {
    return elements;
}

unsigned int VertexBufferLayout::getStride() const {
    return stride;
}
