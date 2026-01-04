#pragma once
#include "Shader.h"
#include "../objects/Object.h"

class Renderer
{
public:
    Shader shader;

    Renderer();
    void draw(Object& obj);
};
