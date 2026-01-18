#pragma once
#include "core/SceneNode.h"
#include "objects/Box.h"
#include "objects/Cylinder.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"

class Box;
class Cylinder;

class StickMan : public SceneNode
{
public:
    /**
     * @brief Construct a StickMan
     * @param scale Scale factor (default = 1.0f)
     * @param material Optional material for all parts
     */
    StickMan(float scale = 1.0f, Material* material = nullptr);

private:
    Cylinder* head;
    Box* body;
    Box* leftArm;
    Box* rightArm;
    Box* leftLeg;
    Box* rightLeg;
};
