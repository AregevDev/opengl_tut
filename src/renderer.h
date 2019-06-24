#ifndef OPENGL_TUT_RENDERER_H
#define OPENGL_TUT_RENDERER_H

#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"
#include <glad/glad.h>

#define GL_CALL(x) clearError(); x; logCall();

static void clearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool logCall() {
    GLenum errcode = glGetError();
    if (errcode) {
        std::ostringstream message;
        message << "OpenGL Error, code = " << errcode << std::endl;
        throw std::runtime_error(message.str());
    }

    return true;
}

class Renderer {
private:

public:
    void draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader);
    void clearBackground(float r, float g, float b, float a) const;
};

#endif //OPENGL_TUT_RENDERER_H
