#include "../scene/Stretcher.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

Stretcher::Stretcher(float L, float W, float H)
{
    matMetal = new Material(new Texture("assets/textures/props/oxygen/metal.png"), { 1,1 });
    matMattress = new Material(new Texture("assets/textures/props/stretcher/red.png"), { 1,1 });
    matStrap = new Material(new Texture("assets/textures/props/stretcher/yellow.png"), { 1,1 });
    matWheel = new Material(new Texture("assets/textures/props/stretcher/wheel_black.png"), { 1,1 });

    matMetal->shininess = 96.0f;
    matMattress->shininess = 12.0f;
    matStrap->shininess = 10.0f;
    matWheel->shininess = 32.0f;

    //dimensions
    float bedThick = 0.45f;
    float mattressH = 0.6f;

    float railRadius = 0.18f;
    float legR = 0.14f;

    float wheelRad = 0.55f;
    float wheelW = 0.25f;

    float bedY = H;
    float baseY = bedY - bedThick * 0.5f;

    //bed base
    bedBase = new Box(W, bedThick, L);
    bedBase->position = { 0.0f, baseY, 0.0f };
    addChild(bedBase);

    //3 mattress
    float mL = L * 0.30f;
    float gap = 0.15f;
    float mY = bedY + mattressH * 0.5f;

    mattress1 = new Box(W * 0.92f, mattressH, mL);
    mattress2 = new Box(W * 0.92f, mattressH, mL);
    mattress3 = new Box(W * 0.92f, mattressH, mL);

    mattress1->position = { 0.0f, mY, -(mL + gap) };
    mattress2->position = { 0.0f, mY, 0.0f };
    mattress3->position = { 0.0f, mY, +(mL + gap) };

    addChild(mattress1);
    addChild(mattress2);
    addChild(mattress3);

    //straps
    float strapH = 0.10f;
    float strapW = W * 0.95f;
    float strapD = 0.28f;

    strap1 = new Box(strapW, strapH, strapD);
    strap2 = new Box(strapW, strapH, strapD);
    strap3 = new Box(strapW, strapH, strapD);

    float strapY = bedY + mattressH - strapH * 0.2f;

    strap1->position = { 0.0f, strapY, -(mL + gap) };
    strap2->position = { 0.0f, strapY, 0.0f };
    strap3->position = { 0.0f, strapY, +(mL + gap) };

    addChild(strap1);
    addChild(strap2);
    addChild(strap3);

    //side rails
    float railY = bedY + mattressH * 0.35f;
    float sideX = (W * 0.5f) + 0.15f;

    railL = new Cylinder(railRadius, L * 1.02f, 28);
    railL->rotation.x = glm::radians(90.0f); 
    railL->position = { -sideX, railY, 0.0f };
    addChild(railL);

    railR = new Cylinder(railRadius, L * 1.02f, 28);
    railR->rotation.x = glm::radians(90.0f);
    railR->position = { +sideX, railY, 0.0f };
    addChild(railR);

    //front/back rails
    float endZ = (L * 0.5f) + 0.15f;

    railFront = new Cylinder(railRadius, W * 1.05f, 28);
    railFront->rotation.z = glm::radians(90.0f); 
    railFront->position = { 0.0f, railY, -endZ };
    addChild(railFront);

    railBack = new Cylinder(railRadius, W * 1.05f, 28);
    railBack->rotation.z = glm::radians(90.0f);
    railBack->position = { 0.0f, railY, +endZ };
    addChild(railBack);

    //Legs
    float legH = bedY - wheelRad; // down to near wheels
    float legY = (bedY - wheelRad) * 0.5f + wheelRad;

    float lx = W * 0.45f;
    float lz = L * 0.42f;

    legFL = new Cylinder(legR, legH, 20); legFL->position = { -lx, legY, -lz }; addChild(legFL);
    legFR = new Cylinder(legR, legH, 20); legFR->position = { +lx, legY, -lz }; addChild(legFR);
    legBL = new Cylinder(legR, legH, 20); legBL->position = { -lx, legY, +lz }; addChild(legBL);
    legBR = new Cylinder(legR, legH, 20); legBR->position = { +lx, legY, +lz }; addChild(legBR);

    //Wheels
    auto makeWheel = [&](Cylinder*& wheel, Cylinder*& hub, float x, float z)
        {
            wheel = new Cylinder(wheelRad, wheelW, 24);
            wheel->rotation.z = glm::radians(90.0f);
            wheel->position = { x, wheelRad, z };
            addChild(wheel);

            hub = new Cylinder(wheelRad * 0.45f, wheelW * 1.02f, 20);
            hub->rotation.z = glm::radians(90.0f);
            hub->position = { x, wheelRad, z };
            addChild(hub);
        };

    makeWheel(wheelFL, hubFL, -lx, -lz);
    makeWheel(wheelFR, hubFR, +lx, -lz);
    makeWheel(wheelBL, hubBL, -lx, +lz);
    makeWheel(wheelBR, hubBR, +lx, +lz);

    //Handles (front/back)
    float handleR = 0.12f;
    float handleLen = W * 0.75f;
    float handleY = bedY + mattressH * 0.65f;

    handleFront = new Cylinder(handleR, handleLen, 22);
    handleFront->rotation.z = glm::radians(90.0f);
    handleFront->position = { 0.0f, handleY, -(L * 0.5f + 0.4f) };
    addChild(handleFront);

    handleBack = new Cylinder(handleR, handleLen, 22);
    handleBack->rotation.z = glm::radians(90.0f);
    handleBack->position = { 0.0f, handleY, +(L * 0.5f + 0.4f) };
    addChild(handleBack);

    setStretcherMaterial();
}

void Stretcher::setStretcherMaterial()
{
    //base + rails + legs + hubs = metal
    bedBase->setMaterial(matMetal);

    railL->setMaterial(matMetal);
    railR->setMaterial(matMetal);
    railFront->setMaterial(matMetal);
    railBack->setMaterial(matMetal);

    legFL->setMaterial(matMetal);
    legFR->setMaterial(matMetal);
    legBL->setMaterial(matMetal);
    legBR->setMaterial(matMetal);

    hubFL->setMaterial(matMetal);
    hubFR->setMaterial(matMetal);
    hubBL->setMaterial(matMetal);
    hubBR->setMaterial(matMetal);

    handleFront->setMaterial(matMetal);
    handleBack->setMaterial(matMetal);

    // mattress = red
   mattress1->setMaterial(matMattress);
   mattress2->setMaterial(matMattress);
   mattress3->setMaterial(matMattress);

    // straps = yellow
    strap1->setMaterial(matStrap);
    strap2->setMaterial(matStrap);
    strap3->setMaterial(matStrap);

    // wheels = black
    wheelFL->setMaterial(matWheel);
    wheelFR->setMaterial(matWheel);
    wheelBL->setMaterial(matWheel);
    wheelBR->setMaterial(matWheel);
}
