#include "Material.h"
#include "Texture.h"
#include "../core/Shader.h" // your existing shader wrapper
#include <glm/gtc/type_ptr.hpp>

Material::Material(Texture* tex, const glm::vec2& tile)
    : diffuse(tex), tiling(tile)
{
    hasTexture = (tex != nullptr);
    updateFromTexture();
}

void Material::bind(Shader& shader, unsigned int unit) const
{
    shader.setBool("hasTexture", hasTexture);
    shader.setVec3("materialColor", baseColor);
    shader.setVec2("uvScale", tiling);
    shader.setFloat("material_shininess", shininess);

    if (hasTexture && diffuse)
    {
        diffuse->bind(unit);
        shader.setInt("tex", (int)unit);
    }
}


void Material::updateFromTexture()
{
    transparent = (diffuse != nullptr) && diffuse->hasAlpha;
}
