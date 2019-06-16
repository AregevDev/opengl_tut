#include "vertexarray.h"
#include <glad/glad.h>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) {
    bind();
    vbo.bind();
    const auto &elements = layout.getElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        std::cout << element.count << std::endl;
        std::cout << element.type << std::endl;
        std::cout << element.normalized << std::endl;
        std::cout << offset << std::endl;
    }
}

void VertexArray::bind() const {
    glBindVertexArray(rendererID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
