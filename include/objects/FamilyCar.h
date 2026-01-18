#pragma once
#include "../core/SceneNode.h"

class Material;
class Box;
class Cylinder;
class Polygon;

class FamilyCar : public SceneNode
{
public:
    FamilyCar();
    void setCarMaterial();
    void setBodyMaterial();
    void setCabinMaterial();
    void setWheelMaterial();


private:
    Box* body = nullptr;
    Box* cabin = nullptr;
    Cylinder* wheels[4] = { nullptr, nullptr, nullptr, nullptr };

    Material* CabinmatFront = nullptr;
    Material* CabinmatBack = nullptr;
    Material* CabinmatRight = nullptr;
    Material* CabinmatLeft = nullptr;
    Material* matRoof = nullptr;
    Material* bodymatFront = nullptr;
    Material* bodymatBack = nullptr;
    Material* bodymatLeft = nullptr;
    Material* bodymatRight = nullptr;
    Material* wheelMatSide = nullptr;
    Material* wheelMatTop = nullptr;
    Material* matTransparente = nullptr;
    Material* frontPanelMat = nullptr;
};