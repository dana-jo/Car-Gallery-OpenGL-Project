#pragma once
#include "../core/SceneNode.h"
#include "../objects/Cylinder.h"

class Box;
class Material;

class TayoBus : public SceneNode
{
public:
    TayoBus();
    ~TayoBus() = default;

private:
    Box* body = nullptr;

    Cylinder* wheels[4]{};
};
