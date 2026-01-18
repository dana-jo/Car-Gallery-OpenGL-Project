#pragma once
#include "core/SceneNode.h"
#include "graphics/Material.h"

class Box;
class Cylinder;

class CartoonCar : public SceneNode
{
public:
    CartoonCar(float scale = 1.0f, Material* faceMat = nullptr);

private:
    Box* body;
    Cylinder* wheels[4];
};
