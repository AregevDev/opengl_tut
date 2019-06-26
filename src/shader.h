#ifndef OPENGL_TUT_SHADER_H
#define OPENGL_TUT_SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
private:
    std::string filepath;
    unsigned int rendererID{};
    ShaderSource shaderSource;
    std::unordered_map<std::string, int> locationCache;

    int getUniformLocation(const std::string &name);
    unsigned int compileShader(unsigned int type);

    ShaderSource parseShader();
    unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader);
public:
    explicit Shader(const std::string &filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void setUniform1f(const std::string &name, float v0);
    void setUniform1i(const std::string &name, int v0);
    void setUniformMat4f(const std::string &name, glm::mat4 v0);
};

#endif //OPENGL_TUT_SHADER_H
