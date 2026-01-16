#pragma once
#include "../core/SceneNode.h"

class Box;
class Cylinder;
class Material;

class MainCar : public SceneNode {
public:
    MainCar();
    ~MainCar() override;

    void setMaterial(Material* mat);

private:
    Box* body = nullptr;
    Cylinder* wheels[4];
    Material* material = nullptr;
};
