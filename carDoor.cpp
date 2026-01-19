#include "CarDoor.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"  
#include <glm/gtc/matrix_transform.hpp>

CarDoor::CarDoor(float w, float h, float d)
{
    Material* transparentMat = new Material(new Texture("assets/ZZZ/transparent.png"));

    // pivot at hinge
    hinge = new SceneNode();
    addChild(hinge);

    doorLeaf = new Box(w, h, d);

    // move door so LEFT edge sits on hinge
    doorLeaf->position = { w * 0.5f, 0.0f, 0.0f };
    doorLeaf->setMaterial(transparentMat);

    hinge->addChild(doorLeaf);
}

void CarDoor::setDoorMaterial(Material* mat)
{
    doorLeaf->setFaceMaterial(BoxFace::Back, mat);
}

void CarDoor::update(float dt, const glm::vec3& cameraPos)
{
    glm::vec3 worldPos = getWorldPosition();
    float dist = glm::distance(worldPos, cameraPos);

    if (!isOpen && dist < openDistance)
        isOpen = true;
    else if (isOpen && dist > closeDistance)
        isOpen = false;

    float target = isOpen ? openAngle : closedAngle;

    hinge->rotation.y = glm::mix(
        hinge->rotation.y,
        target,
        glm::clamp(dt * rotateSpeed, 0.0f, 1.0f)
    );

    SceneNode::update(dt, cameraPos);
}
