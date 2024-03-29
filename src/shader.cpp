#include "shader.h"
#include "renderer.h"

#include <glad/glad.h>

#include <utility>

Shader::Shader(const std::string &filepath) : filepath(filepath), shaderSource(parseShader()) {
    rendererID = createShader(shaderSource.vertexSource, shaderSource.fragmentSource);
}

Shader::~Shader() {
    GL_CALL(glDeleteProgram(rendererID))
}

void Shader::bind() const {
    GL_CALL(glUseProgram(rendererID))
}

void Shader::unbind() const {
    GL_CALL(glUseProgram(0))
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GL_CALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3))
}

void Shader::setUniform1f(const std::string &name, float v0) {
    GL_CALL(glUniform1f(getUniformLocation(name), v0))
}

void Shader::setUniform1i(const std::string &name, int v0) {
    GL_CALL(glUniform1i(getUniformLocation(name), v0))
}

void Shader::setUniformMat4f(const std::string &name, glm::mat4 v0) {
    GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &v0[0][0]))
}

int Shader::getUniformLocation(const std::string &name) {
    if (locationCache.find(name) != locationCache.end()) {
        return locationCache[name];
    }

    int loc = glGetUniformLocation(rendererID, name.c_str());
    if (loc == -1)
        std::cout << "Warning: uniform " << name << " does not exist!";

    locationCache[name] = loc;
    return loc;
}

ShaderSource Shader::parseShader() {
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

unsigned int Shader::compileShader(unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char *src = (type == GL_VERTEX_SHADER ? shaderSource.vertexSource : shaderSource.fragmentSource).c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr))
    GL_CALL(glCompileShader(id))

    int result;
    GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
    if (!result) {
        int len;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len))
        char *message = static_cast<char *>(alloca(len * sizeof(char)));
        GL_CALL(glGetShaderInfoLog(id, len, &len, message))
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        GL_CALL(glDeleteShader(id))
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER);

    GL_CALL(glAttachShader(program, vs))
    GL_CALL(glAttachShader(program, fs))
    GL_CALL(glLinkProgram(program))
    GL_CALL(glValidateProgram(program))

    GL_CALL(glDeleteShader(vs))
    GL_CALL(glDeleteShader(fs))
    return program;
}
