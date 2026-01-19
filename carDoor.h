#pragma once
#include "../core/SceneNode.h"
#include "../objects/Box.h"

class Material;

class CarDoor : public SceneNode
{
public:
    CarDoor(
        float doorWidth,
        float doorHeight,
        float doorDepth
    );

    void update(float dt, const glm::vec3& cameraPos) override;

    void setDoorMaterial(Material* mat);

private:
    SceneNode* hinge = nullptr;
    Box* doorLeaf = nullptr;

    float closedAngle = 0.0f;
    float openAngle = glm::radians(75.0f);

    float rotateSpeed = 2.0f;
    bool isOpen = false;

    float openDistance = 10.0f;
    float closeDistance = 10.0f;
};
