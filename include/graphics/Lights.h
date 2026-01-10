#pragma once
#include <glm/glm.hpp>
#include <string>
#include "core/Shader.h"

struct DirectionalLight {
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    bool enabled = true;

    void upload(Shader& shader, const std::string& uniformName) const
    {
        shader.setVec3(uniformName + ".direction", direction);
        shader.setVec3(uniformName + ".ambient", ambient);
        shader.setVec3(uniformName + ".diffuse", diffuse);
        shader.setVec3(uniformName + ".specular", specular);
        shader.setBool(uniformName + ".enabled", enabled);
    }
};

struct PointLight {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    bool enabled = true;

    void upload(Shader& shader, const std::string& uniformName) const
    {
        shader.setVec3(uniformName + ".position", position);
        shader.setVec3(uniformName + ".ambient", ambient);
        shader.setVec3(uniformName + ".diffuse", diffuse);
        shader.setVec3(uniformName + ".specular", specular);
        shader.setFloat(uniformName + ".constant", constant);
        shader.setFloat(uniformName + ".linear", linear);
        shader.setFloat(uniformName + ".quadratic", quadratic);
        shader.setBool(uniformName + ".enabled", enabled);
    }
};

struct SpotLight {
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff = 0.0f;      // cosine
    float outerCutOff = 0.0f; // cosine
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    bool enabled = true;

    void upload(Shader& shader, const std::string& uniformName) const
    {
        shader.setVec3(uniformName + ".position", position);
        shader.setVec3(uniformName + ".direction", direction);
        shader.setFloat(uniformName + ".cutOff", cutOff);
        shader.setFloat(uniformName + ".outerCutOff", outerCutOff);
        shader.setVec3(uniformName + ".ambient", ambient);
        shader.setVec3(uniformName + ".diffuse", diffuse);
        shader.setVec3(uniformName + ".specular", specular);
        shader.setFloat(uniformName + ".constant", constant);
        shader.setFloat(uniformName + ".linear", linear);
        shader.setFloat(uniformName + ".quadratic", quadratic);
        shader.setBool(uniformName + ".enabled", enabled);
    }
};
