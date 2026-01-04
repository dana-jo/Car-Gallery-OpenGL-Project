#pragma once
#include "../objects/Object.h"
#include "../core/Shader.h"
#include "../graphics/Texture.h"
#include <array>

enum class BoxFace
{
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    BOTTOM = 5
};

class Box : public Object
{
public:
    Box(float width, float height, float depth);

    void draw(Shader& shader) override;
    void setFaceTexture(BoxFace face, Texture* texture);
    void setTexture(Texture* texture);

private:
    std::array<Texture*, 6> faceTextures{};
};
