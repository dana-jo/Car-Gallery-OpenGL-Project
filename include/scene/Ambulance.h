#pragma once
#include "../core/SceneNode.h"

class Box;
class Cylinder;
class Material;

class Ambulance : public SceneNode
{
public:
    Ambulance();
    ~Ambulance() = default;

private:
    Box* cabin = nullptr;
    Box* driverBox = nullptr;
    Box* patientBox = nullptr;
    Cylinder* wheels[4]{};
    Box* redLight = nullptr;
    Box* blueLight = nullptr;

    /*float blinkTimer = 0.0f;
    bool redOn = true;*/
};

