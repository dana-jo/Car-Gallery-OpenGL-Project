#pragma once
#include "../core/SceneNode.h"

class Box;
class Cylinder;
class Material;

class Surroundings : public SceneNode {
public:
    Surroundings(float gallerySize, float t);
    ~Surroundings() override;
};
