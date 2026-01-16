#include "scene/Room1.h"
#include "../objects/Box.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"

Room1::Room1(float w, float d, float h, float t)
{

    Texture* wallTex = new Texture("assets/textures/yellow.png");
    Material* wallMat = new Material(wallTex, { 4.0f, 4.0f });
    float wallY = h / 2.0f;

    // Example: left angled wall
    {
        Box* wall = new Box(t, h, d * 0.7f);
        wall->position = { -2.0f, wallY, -d / 4.0f };
        wall->rotation.y = glm::radians(35.0f);
        wall->setMaterial(wallMat);
        addChild(wall);
    }

    // Example: right angled wall
    {
        Box* wall = new Box(t, h, d * 0.7f);
        wall->position = { 2.0f, wallY, -d / 4.0f };
        wall->rotation.y = glm::radians(-35.0f);
        wall->setMaterial(wallMat);
        addChild(wall);
    }

    // Later:
    // - window
    // - lights
    // - car pedestal
}
