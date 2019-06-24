#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"

const int VERT_COUNT = 4;
const int IND_COUNT = 6;
const int COMPONENT_COUNT = 2;

void resizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // window configuration
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // init GLFW
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW" << std::endl;
        return -1;
    }

    // crate window
    GLFWwindow *window = glfwCreateWindow(500, 500, "window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not create GLFW window" << std::endl;
        return -1;
    }

    // set the window context to current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // load OpenGL proc addresses using Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Could not initialize Glad" << std::endl;
        return -1;
    }

    // vertex positions
    float vertices[VERT_COUNT * COMPONENT_COUNT] = {
            -0.75f, -0.75, // 0
            0.75f, -0.75f,// 1
            0.75f, 0.75f, // 2
            -0.75f, 0.75f // 3
    };

    // indexes
    unsigned int indices[IND_COUNT] = {
            0, 1, 2, // triangle 1
            2, 3, 0 // triangle 2
    };

    VertexArray vao;
    VertexBuffer vbo(vertices, VERT_COUNT * COMPONENT_COUNT * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(COMPONENT_COUNT);
    vao.addBuffer(vbo, layout);

    // create IBO
    IndexBuffer ibo(indices, IND_COUNT);

    // shaders
    Shader shader("shaders/triangle.glsl");
    shader.bind();

    // create renderer used for drawing
    Renderer renderer;

    // assign our uniform with data from the CPU
    float r = 0.0f;
    float inc = 0.05f;

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glfwSetWindowSizeCallback(window, resizeCallback);
        renderer.clearBackground(0.0f, 0.0f, 0.0f, 1.0f);
        shader.setUniform4f("u_color", r, r, r, 1.0);

        if (r > 1.0f)
            inc = -0.05f;
        else if (r < 0.0f)
            inc = 0.05f;
        r += inc;

        renderer.draw(vao, ibo, shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
