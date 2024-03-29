#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>

const int VERT_COUNT = 4;
const int IND_COUNT = 6;
const int COMPONENT_COUNT = 4;

void resizeCallback(GLFWwindow *window, int width, int height) {
    GL_CALL(glViewport(0, 0, width, height))
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
    GLFWwindow *window = glfwCreateWindow(800, 600, "window", nullptr, nullptr);
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
            0.0f, 0.0f, /* position 0 */ 0.0f, 0.0f, /* texture coord 0 */
            100.0f, 0.0f, /* position 1 */ 1.0f, 0.0f, /* texture coord 1 */
            100.0f, 100.0f, /* position 2 */ 1.0f, 1.0f, /* texture coord 2 */
            0.0f, 100.0f, /* position 3 */ 0.0f, 1.0f /* texture coord 3 */
    };

    // indexes
    unsigned int indices[IND_COUNT] = {
            0, 1, 2, // triangle 1
            2, 3, 0 // triangle 2
    };

    GL_CALL(glEnable(GL_BLEND))
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    VertexArray vao;
    VertexBuffer vbo(vertices, VERT_COUNT * COMPONENT_COUNT * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    vao.addBuffer(vbo, layout);

    // create IBO
    IndexBuffer ibo(indices, IND_COUNT);

    // shaders
    Shader shader("shaders/triangle.glsl");
    shader.bind();

    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

    Texture texture("textures/tex.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);

    // create renderer used for drawing
    Renderer renderer;

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glfwSetWindowSizeCallback(window, resizeCallback);
        renderer.clearBackground(0.0f, 0.0f, 0.0f, 1.0f);
        shader.bind();

        // red
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f));
        glm::mat4 mvp = proj * view * model;

        shader.setUniformMat4f("u_mvp", mvp);
        shader.setUniform4f("u_color", 1.0, 0.0, 0.0, 1.0);
        renderer.draw(vao, ibo, shader);

        // cyan
        model = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, 300.0f, 0.0f));
        model *= glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0.0f));
        mvp = proj * view * model;
        shader.setUniformMat4f("u_mvp", mvp);
        shader.setUniform4f("u_color", 0.0, 1.0, 1.0, 1.0);
        renderer.draw(vao, ibo, shader);

        // yellow
        model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 100.0f, 0.0f));
        model *= glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        model *= glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0, 0.0,1.0f));
        mvp = proj * view * model;
        shader.setUniformMat4f("u_mvp", mvp);
        shader.setUniform4f("u_color", 1.0, 1.0, 0.0, 1.0);
        renderer.draw(vao, ibo, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
