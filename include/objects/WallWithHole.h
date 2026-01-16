#pragma once
#include "../core/SceneNode.h"
#include "Box.h"
#include "../graphics/Material.h"

class WallWithHole : public SceneNode
{
public:
    WallWithHole(
        float outerWidth,
        float outerHeight,
        float depth,
        float holeWidth,
        float holeHeight
    );

    void setWallMaterial(Material* mat);
    void setWindowMaterial(Material* mat);

    Box* getWindowBox() const { return window; }

protected:
    Box* left = nullptr;
    Box* right = nullptr;
    Box* top = nullptr;
    Box* bottom = nullptr;
    Box* window = nullptr;
};
