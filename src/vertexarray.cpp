#include "vertexarray.h"
#include "renderer.h"

VertexArray::VertexArray() {
    GL_CALL(glGenVertexArrays(1, &rendererID))
}

VertexArray::~VertexArray() {
    GL_CALL(glDeleteVertexArrays(1, &rendererID))
}

void VertexArray::addBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) {
    bind();
    vbo.bind();
    const auto &elements = layout.getElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto &element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i))
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *) offset))
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    GL_CALL(glBindVertexArray(rendererID))
}

void VertexArray::unbind() const {
    GL_CALL(glBindVertexArray(0))
}
