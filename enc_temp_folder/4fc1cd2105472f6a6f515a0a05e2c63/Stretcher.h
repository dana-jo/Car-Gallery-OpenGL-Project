#pragma once
#include "../core/SceneNode.h"

class Box;
class Cylinder;
class Material;

class Stretcher : public SceneNode
{
public:
    Stretcher(float length = 18.0f, float width = 7.0f, float height = 3.2f);
    ~Stretcher() = default;

    void setStretcherMaterial();

private:
    // ---------- geometry ----------
    // bed + mattress
    Box* bedBase = nullptr;
    Box* mattress1 = nullptr;
    Box* mattress2 = nullptr;
    Box* mattress3 = nullptr;

    // straps
    Box* strap1 = nullptr;
    Box* strap2 = nullptr;
    Box* strap3 = nullptr;

    // side rails / frame
    Cylinder* railL = nullptr;
    Cylinder* railR = nullptr;
    Cylinder* railFront = nullptr;
    Cylinder* railBack = nullptr;

    // legs
    Cylinder* legFL = nullptr;
    Cylinder* legFR = nullptr;
    Cylinder* legBL = nullptr;
    Cylinder* legBR = nullptr;

    // wheels (each wheel = tire + hub)
    Cylinder* wheelFL = nullptr;
    Cylinder* wheelFR = nullptr;
    Cylinder* wheelBL = nullptr;
    Cylinder* wheelBR = nullptr;

    Cylinder* hubFL = nullptr;
    Cylinder* hubFR = nullptr;
    Cylinder* hubBL = nullptr;
    Cylinder* hubBR = nullptr;

    // small handles
    Cylinder* handleFront = nullptr;
    Cylinder* handleBack = nullptr;

    // ---------- materials ----------
    Material* matMetal = nullptr;
    Material* matMattress = nullptr;
    Material* matStrap = nullptr;
    Material* matWheel = nullptr;
};
#pragma once
