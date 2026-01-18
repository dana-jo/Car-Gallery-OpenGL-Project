#include "FamilyCar.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../objects/Polygon.h"
#include "../graphics/Material.h"
#include <glm/gtc/matrix_transform.hpp>

FamilyCar::FamilyCar()
{
    scale = 6.5f;

    float bodyLength = 4.2f * scale;
    float bodyWidth = 1.8f * scale;
    float bodyHeight = 0.6f * scale;

    cabinLength = 3.5f * scale;
    cabinHeight = 0.8f * scale;
    cabinWidth = bodyWidth;

    float wheelRadius = 0.35f * scale;
    float wheelWidth = 0.25f * scale;
    float wheelY = wheelRadius;

    bodymatFront = new Material(new Texture("assets/familyCar/frontBody.png"));
    bodymatBack = new Material(new Texture("assets/familyCar/backBody.png"));
    bodymatLeft = new Material(new Texture("assets/familyCar/leftBody.png"));
    bodymatRight = new Material(new Texture("assets/familyCar/rightBody.png"));

    CabinmatFront = new Material(new Texture("assets/familyCar/frontCabin.png"));
    CabinmatBack = new Material(new Texture("assets/familyCar/backCabin.png"));
    CabinmatLeft = new Material(new Texture("assets/familyCar/leftCabin.png"));
    CabinmatRight = new Material(new Texture("assets/familyCar/rightCabin.png"));

    matRoof = new Material(new Texture("assets/familyCar/roof.png"));
    matRoof1 = new Material(new Texture("assets/familyCar/roof1.png"));

    matTransparente = new Material(new Texture("assets/familyCar/transparente.png"));

    wheelMatSide = new Material(new Texture("assets/familyCar/wheelSide.png"));
    wheelMatTop = new Material(new Texture("assets/familyCar/wheelTop.png"));

    body = new Box(bodyWidth, bodyHeight, bodyLength);
    body->position = { 0.0f, wheelY + bodyHeight * 0.5f, 0.0f };
    addChild(body);

    cabin = new Box(cabinWidth, cabinHeight, cabinLength);
    cabin->position = { 0.0f,
                        body->position.y + bodyHeight * 0.5f + cabinHeight * 0.5f,
                        -bodyLength * 0.5f + cabinLength * 0.5f };
    addChild(cabin);

    float wheelX = bodyWidth * 0.5f + 0.05f;
    float wheelZ = bodyLength * 0.35f;

    for (int i = 0; i < 4; ++i)
        wheels[i] = new Cylinder(wheelRadius, wheelWidth, 24);

    wheels[0]->position = { -wheelX, wheelY,  wheelZ };
    wheels[1]->position = { wheelX, wheelY,  wheelZ };
    wheels[2]->position = { -wheelX, wheelY, -wheelZ };
    wheels[3]->position = { wheelX, wheelY, -wheelZ };

    for (int i = 0; i < 4; ++i)
    {
        wheels[i]->rotation.z = glm::radians(90.0f);
        addChild(wheels[i]);
    }

    setCarMaterial();
}

void FamilyCar::setCarMaterial()
{
    setBodyMaterial();
    setCabinMaterial();
    setWheelMaterial();
    createFrontCabinPanel();
}

void FamilyCar::setBodyMaterial()
{
    body->setFaceMaterial(BoxFace::Front, bodymatFront);
    body->setFaceMaterial(BoxFace::Back, bodymatBack);
    body->setFaceMaterial(BoxFace::Left, bodymatLeft);
    body->setFaceMaterial(BoxFace::Right, bodymatRight);
    body->setFaceMaterial(BoxFace::Top, matRoof);
    body->setFaceMaterial(BoxFace::Bottom, matRoof);
}

void FamilyCar::setCabinMaterial()
{
    cabin->setFaceMaterial(BoxFace::Front, matTransparente); 
    cabin->setFaceMaterial(BoxFace::Back, CabinmatBack);
    cabin->setFaceMaterial(BoxFace::Left, CabinmatRight);
    cabin->setFaceMaterial(BoxFace::Right, CabinmatLeft);
    cabin->setFaceMaterial(BoxFace::Top, matRoof1);
    cabin->setFaceMaterial(BoxFace::Bottom, matTransparente);
}

void FamilyCar::setWheelMaterial()
{
    for (int i = 0; i < 4; ++i) {
        if (wheels[i]) {
            wheels[i]->setPartMaterial(CylinderPart::Side, wheelMatSide);
            wheels[i]->setPartMaterial(CylinderPart::Bottom, wheelMatTop);
            wheels[i]->setPartMaterial(CylinderPart::Top, wheelMatTop);
        }
    }
}

void FamilyCar::createFrontCabinPanel()
{
    float thickness = 0.02f * scale;

    cabinFront = new Polygon({
        {-cabinWidth * 0.50f, -cabinHeight * 0.5f},
        { cabinWidth * 0.50f, -cabinHeight * 0.5f},
        { cabinWidth * 0.50f,  cabinHeight * 0.5f},
        {-cabinWidth * 0.50f,  cabinHeight * 0.5f}
        }, thickness);

    cabinFront->position = {
    0.0f,
    cabin->position.y,
    cabin->position.z +10 
    };

    cabinFront->rotation.x = glm::radians(-30.0f); 

    cabinFront->setMaterial(CabinmatFront);

    addChild(cabinFront);

    cabin->setFaceMaterial(BoxFace::Front, matTransparente);
}
