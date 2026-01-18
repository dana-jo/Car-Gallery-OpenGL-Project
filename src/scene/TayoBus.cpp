#include "scene/TayoBus.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/constants.hpp>

TayoBus::TayoBus(float scale)
{
    // ===============================
    // Base size (REAL bus size)
    // ===============================
    float baseScale = 15.0f;
    float s = baseScale * scale;

    float bodyW = 0.9f;
    float bodyH = 0.5f;
    float bodyD = 0.5f;

    float wheelR = 0.1f;
    float wheelW = 0.05f;

    // ===============================
    // Body
    // ===============================
    body = new Box(
        bodyW * s,
        bodyH * s,
        bodyD * s
    );

    body->position = { 0.0f, bodyH * s * 0.5f, 0.0f };
    addChild(body);

    // ===============================
    // Textures & Materials
    // ===============================
    Material* matFront = new Material(new Texture("assets/textures/tayo_right.png"));
    Material* matBack = new Material(new Texture("assets/textures/tayo_left.png"));
    Material* matLeft = new Material(new Texture("assets/textures/tayo_back.jpg"));
    Material* matRight = new Material(new Texture("assets/textures/tayo_face.jpg"));
    Material* matTop = new Material(new Texture("assets/textures/red.png"));

    body->setFaceMaterial(BoxFace::Front, matFront);
    body->setFaceMaterial(BoxFace::Back, matBack);
    body->setFaceMaterial(BoxFace::Left, matLeft);
    body->setFaceMaterial(BoxFace::Right, matRight);
    body->setFaceMaterial(BoxFace::Top, matTop);

    // ===============================
    // Wheels
    // ===============================
    Material* matWheel = new Material(
        new Texture("assets/textures/black.png")
    );

    for (int i = 0; i < 4; ++i)
    {
        wheels[i] = new Cylinder(
            wheelR * s,
            wheelW * s,
            20
        );

        float sx = (i < 2) ? -0.28f : 0.18f;
        float sz = (i % 2 == 0) ? 0.48f : -0.48f;

        wheels[i]->position = {
            sx * bodyW * s ,
            wheelR * s * 0.9f - 1.f,
            sz * bodyD * s 
        };

        wheels[i]->rotation = {
            glm::half_pi<float>(),
            0.0f,
            0.0f
        };

        wheels[i]->setMaterial(matWheel);
        addChild(wheels[i]);
    }
}
