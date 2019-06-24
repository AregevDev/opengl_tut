#include "renderer.h"

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) {
    shader.bind();
    vao.bind();
    ibo.bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_BYTE, nullptr))
}

void Renderer::clearBackground(float r, float g, float b, float a) const {
    GL_CALL(glClearColor(r, g, b, a))
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
}
