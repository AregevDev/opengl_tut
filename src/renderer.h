#ifndef OPENGL_TUT_RENDERER_H
#define OPENGL_TUT_RENDERER_H

#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"

class Renderer {
private:

public:
    void draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader);
    void clearBackground(float r, float g, float b, float a) const;
};

#endif //OPENGL_TUT_RENDERER_H
