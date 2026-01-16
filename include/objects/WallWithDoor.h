#pragma once
#include "../core/SceneNode.h"
#include "Box.h"

class Material;

class WallWithDoor : public SceneNode
{
public:
    WallWithDoor(
        float outerWidth,   // total wall width
        float outerHeight,  // total wall height
        float depth,        // wall thickness
        float doorWidth,    // door width
        float doorHeight    // door height
    );

    void setWallMaterial(Material* mat);
    void setDoorMaterial(Material* mat);

private:
    Box* left = nullptr;
    Box* right = nullptr;
    Box* top = nullptr;
    Box* door = nullptr;
};
