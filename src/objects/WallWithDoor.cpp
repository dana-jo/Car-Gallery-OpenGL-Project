#include "WallWithDoor.h"
#include "../graphics/Material.h"
#include <stdexcept>

WallWithDoor::WallWithDoor(
    float outerWidth,
    float outerHeight,
    float depth,
    float doorWidth,
    float doorHeight
)
{
    if (doorWidth >= outerWidth || doorHeight >= outerHeight)
        throw std::runtime_error("Door must fit inside wall");

    float ow = outerWidth * 0.5f;
    float oh = outerHeight * 0.5f;
    float dw = doorWidth * 0.5f;
    float dh = doorHeight * 0.5f;

    float sideW = ow - dw;          // width of left/right walls
    float topH = oh - dh;           // height of top piece

    // ---------------- LEFT WALL ----------------
    left = new Box(sideW, outerHeight, depth);
    left->position = { -(dw + sideW * 0.5f), 0.0f, 0.0f };
    addChild(left);

    // ---------------- RIGHT WALL ----------------
    right = new Box(sideW, outerHeight, depth);
    right->position = { (dw + sideW * 0.5f), 0.0f, 0.0f };
    addChild(right);

    // ---------------- TOP ----------------
    top = new Box(doorWidth, outerHeight - doorHeight, depth);
    top->position = { 0.0f, oh - topH, 0.0f };
    addChild(top);

    // ---------------- DOOR ----------------

    doorLeaf = new Box(doorWidth, doorHeight, depth);
    doorLeaf->position = { 0.0f, -oh + dh, depth * 0.51f };

    addChild(doorLeaf);

    closedPos = doorLeaf->position;

    // Slide to the RIGHT into the wall
    openPos = closedPos + glm::vec3(doorWidth, 0.0f, 0.0f);

}

void WallWithDoor::setWallMaterial(Material* mat)
{
    left->setMaterial(mat);
    right->setMaterial(mat);
    top->setMaterial(mat);
}

void WallWithDoor::setDoorMaterial(Material* mat)
{
    doorLeaf->setMaterial(mat);
}

void WallWithDoor::update(float dt, const glm::vec3& cameraPos)
{
    glm::vec3 wallWorldPos = getWorldPosition();
    float dist = glm::distance(wallWorldPos, cameraPos);

    if (!isOpen && dist < openDistance)
        isOpen = true;
    else if (isOpen && dist > closeDistance)
        isOpen = false;


    glm::vec3 target = isOpen ? openPos : closedPos;

    doorLeaf->position = glm::mix(
        doorLeaf->position,
        target,
        glm::clamp(dt * slideSpeed, 0.0f, 1.0f)
    );

    SceneNode::update(dt, cameraPos);
}


