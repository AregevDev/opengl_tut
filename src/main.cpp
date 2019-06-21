#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

const int VERT_COUNT = 4;
const int IND_COUNT = 6;
const int COMPONENT_COUNT = 2;

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderSource parseShader(const std::string &filepath) {
    std::ifstream stream(filepath);
    enum ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    std::stringstream ss[2];
    std::string line;
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int compileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char *message = static_cast<char *>(alloca(len * sizeof(char)));
        glGetShaderInfoLog(id, len, &len, message);
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
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
    ShaderSource source = parseShader("shaders/triangle.glsl");
    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    // assign our uniform with data from the CPU
    unsigned int colorLocation = glGetUniformLocation(shader, "u_color");
    float r = 0.0f;
    float inc = 0.05f;

    // main loop
    while (!glfwWindowShouldClose(window)) {
        glfwSetWindowSizeCallback(window, resizeCallback);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform4f(colorLocation, r, r, r, 1.0);
        glDrawElements(GL_TRIANGLES, IND_COUNT, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f)
            inc = -0.05f;
        else if (r < 0.0f)
            inc = 0.05f;

        r += inc;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
