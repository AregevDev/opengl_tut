#include "renderer.h"

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader) {
    shader.bind();
    vao.bind();
    ibo.bind();
    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clearBackground(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
