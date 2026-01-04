#include "../core/Renderer.h"

void Renderer::draw(Object& obj)
{
    obj.draw(shader);
}
