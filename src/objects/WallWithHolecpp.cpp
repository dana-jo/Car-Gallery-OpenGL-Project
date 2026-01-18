#include "objects/WallWithHole.h"
#include <stdexcept>

WallWithHole::WallWithHole(
    float outerW,
    float outerH,
    float depth,
    float holeW,
    float holeH
)
{
    if (holeW >= outerW || holeH >= outerH)
        throw std::runtime_error("Hole must be smaller than wall");

    float ow = outerW * 0.5f;
    float oh = outerH * 0.5f;
    float hw = holeW * 0.5f;
    float hh = holeH * 0.5f;

    float sideW = ow - hw;
    float topBotH = oh - hh;
    depth /= 2.0f;

    // LEFT
    left = new Box(sideW, outerH, depth);
    left->position = { -(hw + sideW * 0.5f), 0, 0 };
    addChild(left);

    // RIGHT
    right = new Box(sideW, outerH, depth);
    right->position = { (hw + sideW * 0.5f), 0, 0 };
    addChild(right);

    // TOP
    top = new Box(outerW - 2*sideW, topBotH, depth);
    top->position = { 0,  hh + topBotH * 0.5f, 0 };
    addChild(top);

    // BOTTOM
    bottom = new Box(outerW - 2*sideW, topBotH , depth);
    bottom->position = { 0, -(hh + topBotH * 0.5f), 0 };
    addChild(bottom);

    // WINDOW
    window = new Box(holeW, holeH, depth * 0.1f);
    window->position = { 0, 0, 0 };
	//window->ignoreCollision = true; // if u want to pass through the window

    collider = new BoxCollider({ glm::max(outerW,20.0f),  glm::max(outerH,20.0f), glm::max(depth,20.0f)});

    addChild(window);
}
    

void WallWithHole::setWallMaterial(Material* mat)
{
    left->setMaterial(mat);
    right->setMaterial(mat);
    top->setMaterial(mat);
    bottom->setMaterial(mat);
}

void WallWithHole::setWindowMaterial(Material* mat)
{
    window->setMaterial(mat);
}

