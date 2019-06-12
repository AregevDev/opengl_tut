#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "vertexbuffer.h"
#include "indexbuffer.h"

const int VERT_COUNT = 4;
const int IND_COUNT = 6;
const int COMPONENT_COUNT = 2;

static std::string ReadFileToString(const std::string &filename) {
    std::ifstream ifs(filename);
    std::stringstream buffer;
    std::string line;

    while (getline(ifs, line)) {
        buffer << line << "\n";
    }

    ifs.close();
    return buffer.str();
}

static void CheckShaders(GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "shader compilation failed" << infoLog << std::endl;
    }
}

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
    GLFWwindow *window = glfwCreateWindow(640, 480, "window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Could not create GLFW window" << std::endl;
        return -1;
    }

    // set the window context to current
    glfwMakeContextCurrent(window);

    // load OpenGL proc addresses using Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Could not initialize Glad" << std::endl;
        return -1;
    }

    // crate VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    // vertex positions
    float vertices[VERT_COUNT * COMPONENT_COUNT] = {
            -0.75f, -0.75, // 0
            0.75f, -0.75f,// 1
            0.75f, 0.75f, // 2
            -0.75f, 0.75f // 3
    };

    VertexBuffer vbo(vertices, VERT_COUNT * COMPONENT_COUNT * sizeof(float));
    unsigned int startIdx = 0;
    glVertexAttribPointer(startIdx, COMPONENT_COUNT, GL_FLOAT, false, sizeof(float) * COMPONENT_COUNT, nullptr);

    // indexes
    unsigned int indices[IND_COUNT] = {
            0, 1, 2, // triangle 1
            2, 3, 0 // triangle 2
    };

    // create IBO
    IndexBuffer ibo(indices, IND_COUNT);

    // shaders
    // compile vertex shader
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertSource = ReadFileToString("shaders/triangle_v.glsl");
    const char *vertStr = vertSource.c_str();

    glShaderSource(vertShader, 1, &vertStr, nullptr);
    glCompileShader(vertShader);

    // check for success compiling vertex
    CheckShaders(vertShader);

    // compile fragment shader
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragSource = ReadFileToString("shaders/triangle_f.glsl");
    const char *fragStr = fragSource.c_str();

    glShaderSource(fragShader, 1, &fragStr, nullptr);
    glCompileShader(fragShader);

    // check for success compiling fragment
    CheckShaders(fragShader);

    // create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glfwSetWindowSizeCallback(window, resizeCallback);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, IND_COUNT, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
