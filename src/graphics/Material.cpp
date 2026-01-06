#include "Material.h"
#include "Texture.h"
#include "../core/Shader.h" // your existing shader wrapper
#include <glm/gtc/type_ptr.hpp>

Material::Material(Texture* tex, const glm::vec2& tile)
    : diffuse(tex), tiling(tile)
{
    updateFromTexture();
}

void Material::bind(Shader& shader, unsigned int unit) const
{
    if (diffuse)
    {
        diffuse->bind(unit);
        shader.setInt("tex", (int)unit);
    }
    shader.setVec2("uvScale", tiling);
}

void Material::updateFromTexture()
{
    transparent = (diffuse != nullptr) && diffuse->hasAlpha;
}
