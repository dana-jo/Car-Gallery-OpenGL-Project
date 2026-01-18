#include "../scene/OxygenTank.h"
#include "../objects/Cylinder.h"
#include "../objects/Box.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

OxygenTank::OxygenTank(float r, float h)
{
    // ---------- MATERIALS ----------
    matBody = new Material(new Texture("assets/textures/props/oxygen/tank_green.png"), { 1,1 });
    matMetal = new Material(new Texture("assets/textures/props/oxygen/metal.png"), { 1,1 });
    matGreen = new Material(new Texture("assets/textures/props/oxygen/green.png"), { 1,1 });
    matPressure = new Material(new Texture("assets/textures/props/oxygen/pressure.png"), { 1,1 });

    matBody->shininess = 60.0f;
    matMetal->shininess = 96.0f;
    matGreen->shininess = 60.0f;
    matPressure->shininess = 96.0f;

    // ---------- MAIN BODY ----------
    body = new Cylinder(r, h, 32);
    body->position = { 0.0f, h * 0.5f, 0.0f };
    addChild(body);

    // ---------- SHOULDER (rounded top) ----------
    shoulder = new Cylinder(r * 1.05f, h * 0.12f, 32);
    shoulder->position = { 0.0f, h + (h * 0.12f) * 0.5f, 0.0f };
    addChild(shoulder);

    // ---------- NECK ----------
    float neckH = h * 0.15f;
    neck = new Cylinder(r * 0.35f, neckH, 24);
    neck->position = { 0.0f, h + h * 0.12f + neckH * 0.5f, 0.0f };
    addChild(neck);

    // ---------- REGULATOR BLOCK ----------
    regulator = new Box(r * 1.1f, neckH * 0.6f, r * 0.8f);
    regulator->position = {
        0.0f,
        h + h * 0.12f + neckH + (neckH * 0.6f) * 0.5f,
        0.0f
    };
    addChild(regulator);

    // ---------- PRESSURE GAUGES ----------
    float gR = r * 0.45f;
    float gD = r * 0.15f;

    gaugeL = new Cylinder(gR, gD, 20);
    gaugeL->rotation.x = glm::radians(90.0f);
    gaugeL->position = {
        -r * 0.9f,
        regulator->position.y,
        0.0f
    };
    addChild(gaugeL);

    gaugeR = new Cylinder(gR * 0.85f, gD, 20);
    gaugeR->rotation.x = glm::radians(90.0f);
    gaugeR->position = {
        r * 0.8f,
        regulator->position.y,
        0.0f
    };
    addChild(gaugeR);

    // ---------- OUTLET PIPE ----------
    outlet = new Cylinder(r * 0.18f, r * 0.8f, 20);
    outlet->rotation.z = glm::radians(90.0f);
    outlet->position = {
        r * 0.5f,
        regulator->position.y,
        r * 0.5f
    };
    addChild(outlet);

    setTankMaterial();
}

void OxygenTank::setTankMaterial()
{
    body->setMaterial(matBody);
    shoulder->setMaterial(matGreen);

    neck->setMaterial(matMetal);
    regulator->setMaterial(matMetal);
    gaugeL->setMaterial(matPressure);
    gaugeR->setMaterial(matMetal);
    outlet->setMaterial(matGreen);

}
