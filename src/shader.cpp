#include "shader.h"

#include <utility>

Shader::Shader(std::string filepath) : filepath(std::move(filepath)), shaderSource(parseShader()) {
    rendererID = createShader(shaderSource.vertexSource, shaderSource.fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(rendererID);
}

void Shader::bind() const {
    glUseProgram(rendererID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
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

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}
