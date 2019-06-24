#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    GL_CALL(glGenBuffers(1, &rendererID))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID))
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer()  {
    GL_CALL(glDeleteBuffers(1, &rendererID))
}

void VertexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID))
}

void VertexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
}
