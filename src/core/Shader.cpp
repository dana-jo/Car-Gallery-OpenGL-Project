#include "../core/Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

static std::string readFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream buffer;

    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}


Shader::Shader() : ID(0) {}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compile error:\n" << infoLog << std::endl;
    }

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compile error:\n" << infoLog << std::endl;
    }

    // Shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "Shader program link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(mat)
    );
}

