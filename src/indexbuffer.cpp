#include "indexbuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count(count) {
    GL_CALL(glGenBuffers(1, &rendererID))
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID))
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW))
}

IndexBuffer::~IndexBuffer()  {
    GL_CALL(glDeleteBuffers(1, &rendererID))
}

void IndexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID))
}

void IndexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

unsigned int IndexBuffer::getCount() const {
    return count;
}
