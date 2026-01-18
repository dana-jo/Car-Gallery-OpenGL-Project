#pragma once
#include <glm/glm.hpp>

class Texture;
class Shader;

class Material
{
public:
    Texture* diffuse = nullptr;
    glm::vec2 tiling = { 1.0f, 1.0f };
    float shininess = 32.0f;

    glm::vec3 baseColor = glm::vec3(1.0f);
    bool hasTexture = false;

    bool transparent = false;

    Material() = default;
    Material(Texture* tex, const glm::vec2& tile = { 1.0f, 1.0f });

    // Binds textures/sampler uniforms needed by the shader.
    // unit is the texture unit the diffuse will be bound to (default 0).
    void bind(Shader& shader, unsigned int unit = 0) const;

    // Call this when you change the texture to update transparency flag.
    void updateFromTexture();
};
