#include "scene/Room3.h"
#include "WallWithHole.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/WallWithDoor.h"
#include <scene/TayoBus.h>
#include <scene/CartoonCar.h>
#include <Lights.h>
#include <scene/StickMan.h>

Room3::Room3(float gWidth, float gHeight, float gDepth, float g)
{
    // ===============================
    // Textures & Materials
    // ===============================
    Material* plate1Mat = new Material(new Texture("assets/textures/whiteMarble.jpg"));
    Material* plate2Mat = new Material(new Texture("assets/textures/offwhite.jpg"));
    Material* woodMat = new Material(new Texture("assets/textures/cardboard-texture.jpg"));

    // ===============================
    // Tayo display platforms
    // ===============================
    Cylinder* plate1 = new Cylinder(10.f, 1.4f, 32);
    plate1->position = { -9.0f, 0.7f, -9.0f };
    plate1->setMaterial(plate2Mat);
    addChild(plate1);

    Box* plate2 = new Box(17, 1.4, 17);
    plate2->position = { 11.5f, 0.7f, -10.0f };
    plate2->setMaterial(plate2Mat);
    addChild(plate2);

    // ===============================
    // Tayo buses
    // ===============================
    TayoBus* bus1 = new TayoBus();
    bus1->position = { -9.0f, 2.6f, -9.0f };
    bus1->rotation.y = glm::radians(-65.0f);
    addChild(bus1);

    // ===============================
    // Cartoon Cars
    // ===============================
    CartoonCar* mainCar = new CartoonCar(1.0f, new Material(new Texture("assets/textures/face1.jpg")));
    mainCar->position = { 11.f, 6.0f, -11.f };
    mainCar->rotation.y = glm::radians(-90.0f);
    addChild(mainCar);

    CartoonCar* smallCar = new CartoonCar(0.45f, new Material(new Texture("assets/textures/face2.jpg")));
    smallCar->position = { 16.5f, 3.4f, -5.0f };
    smallCar->rotation.y = glm::radians(-130.0f);
    addChild(smallCar);

    // ===============================
    // Wall paintings
    // ===============================
    float bigW = 8.0f, bigH = 12.0f, bigD = 0.7f;
    float smallW = 5.0f, smallH = 7.0f, smallD = 0.6f;

    Material* bigMat = new Material(new Texture("assets/textures/TayoPoster.jpg"));
    Material* leftMat = new Material(new Texture("assets/textures/DIYPoster.jpg"));
    Material* rightMat = new Material(new Texture("assets/textures/pic3.jpg"));

    // BIG
    Box* bigFrame = new Box(bigW + 1.0f, bigH + 1.0f, 0.4f);
    bigFrame->position = { -5.0f, 18.0f, 18.75f };
    bigFrame->setMaterial(woodMat);
    addChild(bigFrame);

    Box* bigPic = new Box(bigW, bigH, bigD);
    bigPic->position = { -5.0f, 18.0f, 18.8f };
    bigPic->rotation.y = glm::radians(180.0f);
    bigPic->setMaterial(plate1Mat);
    bigPic->setFaceMaterial(BoxFace::Front, bigMat);
    addChild(bigPic);

    // LEFT
    Box* leftFrame = new Box(smallW + 0.6f, smallH + 0.6f, 0.35f);
    leftFrame->position = { -13.0f, 18.0f, 18.75f };
    leftFrame->setMaterial(woodMat);
    addChild(leftFrame);

    Box* leftPic = new Box(smallW, smallH, smallD);
    leftPic->position = { -13.0f, 18.0f, 18.8f };
    leftPic->rotation.y = glm::radians(180.0f);
    leftPic->setMaterial(leftMat);
    addChild(leftPic);

    // RIGHT
    Box* rightFrame = new Box(smallW + 0.6f, smallH + 0.6f, 0.35f);
    rightFrame->position = { 3.0f, 18.0f, 18.75f };
    rightFrame->setMaterial(woodMat);
    addChild(rightFrame);

    Box* rightPic = new Box(smallW, smallH, smallD);
    rightPic->position = { 3.0f, 18.0f, 18.8f };
    rightPic->rotation.y = glm::radians(180.0f);
    rightPic->setMaterial(rightMat);
    addChild(rightPic);

    // ===============================
    // Table and legs
    // ===============================
    float tableW = 16.0f, tableH = 1.0f, tableD = 3.5f;
    glm::vec3 tablePos = { -5.0f, 4.5f, 17.8f };

    Box* table = new Box(tableW, tableH, tableD);
    table->position = tablePos;
    table->setMaterial(woodMat);
    addChild(table);

    float legH = 4.0f, legW = 0.7f;
    for (int i = 0; i < 4; i++)
    {
        float sx = (i < 2) ? -tableW * 0.45f : tableW * 0.45f;
        float sz = (i % 2 == 0) ? -tableD * 0.35f : tableD * 0.35f;

        Box* leg = new Box(legW, legH, legW);
        leg->position = { tablePos.x + sx, tablePos.y - legH * 0.5f, tablePos.z + sz };
        leg->setMaterial(woodMat);
        addChild(leg);
    }

    // ===============================
    // Small Tayo toys on table
    // ===============================
    float toyY = tablePos.y + tableH * 0.5f + 0.1f;
    float toyZ = tablePos.z;

    for (int i = -1; i <= 1; i++)
    {
        TayoBus* toy = new TayoBus();
        toy->position = { tablePos.x + i * 4.5f, toyY, toyZ };
        toy->scale = { 0.2f, 0.2f, 0.2f };
        toy->rotation.y = glm::radians(40.0f);
        addChild(toy);
    }

    // ===============================
    // StickMan
    // ===============================
    StickMan* stickyMan = new StickMan(2.5f, woodMat);
    stickyMan->position = { -10.0f, 3.f, 8.0f };
    stickyMan->rotation.y = glm::radians(90.0f);
    addChild(stickyMan);

    // ===============================
    // Floor (Gazon carpet)
    // ===============================
    Material* gazon1Mat = new Material(new Texture("assets/textures/gazon.jpg"), { 8.0f, 6.0f });
    Material* gazon2Mat = new Material(new Texture("assets/textures/gazon.jpg"), { 6.0f, 2.0f });

    Box* floor1 = new Box(gWidth - 80.f, 0.2f, gDepth - 0.25f * gDepth);
    floor1->position = { 0.0f, 0.35f, -0.12f * gDepth };
    floor1->setMaterial(gazon1Mat);
    addChild(floor1);

    Box* floor2 = new Box(0.75f * (gWidth - 80.f), 0.2f, 0.322f * (gDepth - 0.25f * gDepth));
    floor2->position = { -5.f, 0.35f, 0.375f * gDepth };
    floor2->setMaterial(gazon2Mat);
    addChild(floor2);

    // ===============================
    // Walls
    // ===============================
    Material* wallMat = new Material(new Texture("assets/textures/white.png"), { 2,2 });
    Material* windowMat = new Material(new Texture("assets/textures/window1.png"), { 1,1 });
    Material* doorMat = new Material(new Texture("assets/textures/door_frame.png"), { 1,1 });

    auto* wallFront = new WallWithHole(30.0f, 40.0f, 0.01f, 20, 30);
    wallFront->position = { -5.0f, 20.0f, 20.0f };
    wallFront->setWallMaterial(wallMat);
    addChild(wallFront);

    auto* wallLeft = new WallWithHole(30.0f, 40.0f, 0.2f, 20, 30);
    wallLeft->position = { 20.0f, 20.0f, -5.0f };
    wallLeft->rotation.y = glm::radians(90.0f);
    wallLeft->setWallMaterial(wallMat);
    wallLeft->setWindowMaterial(windowMat);
    addChild(wallLeft);

    WallWithDoor* door3 = new WallWithDoor(10.0f * 1.41f, 40.0f, 0.2f, 9.0f, 25.0f);
    door3->position = { 15.0f, 20.0f, 15.0f };
    door3->rotation.y = glm::radians(45.0f);
    door3->setWallMaterial(wallMat);
    door3->setDoorMaterial(doorMat);
    addChild(door3);
}
