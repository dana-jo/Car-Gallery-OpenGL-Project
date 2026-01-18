#include "scene/StickMan.h"

StickMan::StickMan(float scale, Material* material)
{
    if (!material)
    {
        Texture* defaultTex = new Texture("assets/textures/white.png");
        material = new Material(defaultTex);
    }

    float headRadius = 0.5f * scale;
    float bodyHeight = 1.2f * scale;
    float limbLength = 0.8f * scale;
    float limbWidth = 0.2f * scale;

    // HEAD
    head = new Cylinder(headRadius, limbWidth , 16);
    head->position = { 0.0f, bodyHeight + headRadius, 0.0f };
    head->rotation.x = glm::radians(90.0f);
    head->setMaterial(material);
    addChild(head);

    // BODY
    body = new Box(limbWidth, bodyHeight, limbWidth);
    body->position = { 0.0f, bodyHeight / 2.0f, 0.0f };
    body->setMaterial(material);
    addChild(body);

    // ARMS
    leftArm = new Box(limbLength, limbWidth, limbWidth);
    leftArm->position = { -limbLength / 2.0f, bodyHeight * 0.75f, 0.0f };
    leftArm->setMaterial(material);
    addChild(leftArm);

    rightArm = new Box(limbLength, limbWidth, limbWidth);
    rightArm->position = { limbLength / 2.0f, bodyHeight * 0.75f, 0.0f };
    rightArm->setMaterial(material);
    addChild(rightArm);

    Box* hip = new Box(limbWidth * 3.f, limbWidth, limbWidth);
    hip->position = { 0.0f, -limbLength/7.5f, 0.0f };
    addChild(hip);

    // LEGS
    leftLeg = new Box(limbWidth, limbLength, limbWidth);
    leftLeg->position = { -limbWidth, -limbLength / 1.5f, 0.0f };
    leftLeg->setMaterial(material);
    addChild(leftLeg);

    rightLeg = new Box(limbWidth, limbLength, limbWidth);
    rightLeg->position = { limbWidth, -limbLength / 1.5f, 0.0f };
    rightLeg->setMaterial(material);
    addChild(rightLeg);
}
