#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../core/Shader.h"

class Skybox
{
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int cubemapTexture = 0;

    Shader shader;

    void loadCubemap(const std::vector<std::string>& faces);
};
