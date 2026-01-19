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
    void createFrontCabinPanel();


private:
    Box* body = nullptr;
    Box* cabin = nullptr;
    Cylinder* wheels[4] = { nullptr, nullptr, nullptr, nullptr };
    Polygon* cabinFront = nullptr;

    float scalec;
    float cabinWidth;
    float cabinHeight;
    float cabinLength;
    float bodyLength;

    Material* CabinmatFront = nullptr;
    Material* CabinmatBack = nullptr;
    Material* CabinmatRight = nullptr;
    Material* CabinmatLeft = nullptr;
    Material* matRoof = nullptr;
    Material* matRoof1 = nullptr;
    Material* bodymatFront = nullptr;
    Material* bodymatBack = nullptr;
    Material* bodymatLeft = nullptr;
    Material* bodymatRight = nullptr;
    Material* wheelMatSide = nullptr;
    Material* wheelMatTop = nullptr;
    Material* matTransparente = nullptr;
};
