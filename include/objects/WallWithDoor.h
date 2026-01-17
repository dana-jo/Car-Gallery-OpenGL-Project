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

    void update(float dt, const glm::vec3& cameraPos) override;


    void setWallMaterial(Material* mat);
    void setDoorMaterial(Material* mat);

private:

    Box* doorLeaf = nullptr;

    glm::vec3 closedPos;
    glm::vec3 openPos;

    float slideSpeed = 3.0f; // units per second
    bool isOpen = false;

    float openDistance = 20.0f;
    float closeDistance = 25.0f;

    Box* left = nullptr;
    Box* right = nullptr;
    Box* top = nullptr;
};
