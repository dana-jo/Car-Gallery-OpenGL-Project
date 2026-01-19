#include "scene/Ambulance.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
//#include "../graphics/Lights.h"

#include <glm/gtc/constants.hpp>


Ambulance::Ambulance()
{

    Texture* texRed = new Texture("assets/textures/red.png");
    Texture* texBlue = new Texture("assets/textures/blue.png");
    Texture* texWhite = new Texture("assets/textures/white.png");

    Material* matRed = new Material(texRed);
    Material* matBlue = new Material(texBlue);
    Material* matWhite = new Material(texWhite);

    // ===============================
    // 1) Driver cabin (front)
    // ===============================
    // 1- down side

    Texture* texlights = new Texture("assets/textures/Ambulance-lights.png");
    Texture* texFs = new Texture("assets/textures/ambulance-frontside.jpg");
    Material* mat = new Material(texWhite);

    cabin = new Box(1.f, 0.35f, 0.4f);
    cabin->position = { 0.0f, 0.27f, .5f };
    cabin->setMaterial(mat);
    cabin->setFaceMaterial(BoxFace::Front, new Material(texlights));
    cabin->setFaceMaterial(BoxFace::Top, matRed);
    cabin->setFaceMaterial(BoxFace::Right, new Material(texFs));
    cabin->setFaceMaterial(BoxFace::Left,new Material(texFs));
    addChild(cabin);

    // 2- up side
    Texture* texFrontGlass = new Texture("assets/textures/glassfront.png");
    Texture* texSideGlass = new Texture("assets/textures/glassSide.png");
    Material* matFrontGLass = new Material(texFrontGlass);
    Material* matSideGLass = new Material(texSideGlass);

    driverBox = new Box(.99f, 0.8f, 0.3f);
    driverBox->position = { 0.0f, 0.25f*2, .4f };
    driverBox->setMaterial(mat);
    driverBox->setFaceMaterial(BoxFace::Front, matFrontGLass);
    driverBox->setFaceMaterial(BoxFace::Right, matSideGLass);
    driverBox->setFaceMaterial(BoxFace::Left, matSideGLass);
    addChild(driverBox);


    // ===============================
    // 2) Patient compartment (back)
    // ===============================

    patientBox = new Box(1.f, 0.8f, 1.4f);
    patientBox->position = { 0.0f, 0.5f, -0.4f };

    Texture* texBRS = new Texture("assets/textures/Ambulance-right.jpg");//back-right-side
    Texture* texBLS = new Texture("assets/textures/Ambulance-left.jpg");
    Texture* texBBS = new Texture("assets/textures/Ambulance-back.png");
    Material* matBRS = new Material(texBRS);
    Material* matBLS = new Material(texBLS);
    Material* matBBS = new Material(texBBS);

    patientBox->setFaceMaterial(BoxFace::Right, matBRS);
    patientBox->setFaceMaterial(BoxFace::Left, matBLS);
    patientBox->setFaceMaterial(BoxFace::Back, matBBS);
    patientBox->setFaceMaterial(BoxFace::Top, matWhite);
    patientBox->setFaceMaterial(BoxFace::Bottom,matWhite);

    addChild(patientBox);

 // ==============================
 // 4) Emergency lights (top)
 // ==============================

    // Light size
    float lx = 0.33f, ly = 0.15f , lz = 0.15f;

    // Height above patient box
    float lightHeight = 0.45f;

    //Red light (left)
    redLight = new Box(lx, ly, lz);
    redLight->position = { -0.25f, lightHeight, 0.7f };
    //SpotLight* light = new SpotLight();

    redLight->setMaterial(matRed);
    patientBox->addChild(redLight);

    //White light (middle)
    Box* whiteLight = new Box(0.15, ly, lz);
    whiteLight->position = { 0.0f, lightHeight, 0.7f };
    whiteLight->setMaterial(matWhite);
    patientBox->addChild(whiteLight);

    //Blue light (right)
    blueLight = new Box(lx, ly, lz);
    blueLight->position = { 0.25f, lightHeight, 0.7f };
    blueLight->setMaterial(matBlue);
    patientBox->addChild(blueLight);

    // ===============================
    // 3) Wheels (4 cylinders)
    // ===============================

    Texture* texWheel = new Texture("assets/textures/wheel.png");
    Material* matWheel = new Material(texWheel);
    Texture* texTire = new Texture("assets/textures/tireTexture.jpg");
    Material* matTire = new Material(texTire);

    float wheelR = 0.2f;
    float wheelW = 0.1f;
    for (int i = 0; i < 4; ++i)
    {
        wheels[i] = new Cylinder(wheelR, wheelW, 20);

        float sx = (i < 2) ? -0.5f : 0.5f;      // left / right
        float sz = (i % 2 == 0) ? 0.4f : -0.8f; // front / back

        wheels[i]->position = { sx, wheelR * 0.5f, sz };
        wheels[i]->rotation = {0.0f ,0.0f, glm::half_pi<float>()  };
        wheels[i]->setMaterial(matWheel);
        wheels[i]->setPartMaterial(CylinderPart::Side, matTire);
        wheels[i]->setPartMaterial(CylinderPart::Bottom, matWheel);
        wheels[i]->setPartMaterial(CylinderPart::Top,matWheel);

        addChild(wheels[i]);
    }
}

