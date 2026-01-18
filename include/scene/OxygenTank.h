#pragma once
#include "../core/SceneNode.h"

class Cylinder;
class Box;
class Material;

class OxygenTank : public SceneNode
{
public:
    OxygenTank(float r = 0.9f, float h = 7.5f);
    ~OxygenTank() = default;

    void setTankMaterial();

private:
    // geometry
    Cylinder* body = nullptr;
    Cylinder* shoulder = nullptr;
    Cylinder* neck = nullptr;
    Cylinder* gaugeL = nullptr;
    Cylinder* gaugeR = nullptr;
    Cylinder* outlet = nullptr;
    Box* regulator = nullptr;

    // materials
    Material* matBody = nullptr;
    Material* matMetal = nullptr;
    Material* matGreen = nullptr;
    Material* matPressure = nullptr;
};
