#pragma once
#include "core/SceneNode.h"
#include "objects/Cylinder.h"

class Box;
class Cylinder;

class TayoBus : public SceneNode
{
public:
    TayoBus(float scale = 1.0f);

private:
    Box* body;
    Cylinder* wheels[4];
};
