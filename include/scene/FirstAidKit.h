#pragma once
#include "../core/SceneNode.h"

class Box;
class Material;

class FirstAidKit : public SceneNode
{
public:
    FirstAidKit(float w = 3.8f, float h = 2.0f, float d = 3.0f);
    ~FirstAidKit() = default;

    void setKitMaterial();

private:
    // geometry
    Box* body = nullptr;
    Box* crossV = nullptr;
    Box* crossH = nullptr;

    // materials (FamilyCar style)
    Material* matFront = nullptr;
    Material* matBack = nullptr;
    Material* matLeft = nullptr;
    Material* matRight = nullptr;
    Material* matTop = nullptr;
    Material* matBottom = nullptr;

    Material* matCross = nullptr;
};
#pragma once
