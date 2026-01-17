#include "scene/Room4.h"
#include "WallWithHole.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/WallWithDoor.h"

Room4::Room4(float gWidth, float gHeight, float gDepth, float g)
{
    Texture* wallTex = new Texture("assets/textures/white.png");
    Texture* windowTex = new Texture("assets/textures/window1.png");
	Texture* doorTex = new Texture("assets/textures/door_frame.png");

    Material* wallMaterial = new Material(wallTex, { 2,2 });
    Material* windowMaterial = new Material(windowTex, { 1,1 });
	Material* doorMaterial = new Material(doorTex, { 1.0f, 1.0f });

    float wallW = 30.0f;
    float wallH = 40.0f;
    float depth = 0.2f;

    // Front wall
    auto* wallFront = new WallWithHole(wallW, wallH, depth, 20, 30);
    wallFront->position = { +5.0f, 20.0f, +20.0f };
    wallFront->setWallMaterial(wallMaterial);
    wallFront->setWindowMaterial(windowMaterial);
    addChild(wallFront);

    // Right wall
    auto* wallRight = new WallWithHole(wallW, wallH, depth, 20, 30);

    wallRight->position = { -20.0f, 20.0f, -5.0f };
    wallRight->rotation.y = glm::radians(90.0f);

    wallRight->setWallMaterial(wallMaterial);
    wallRight->setWindowMaterial(windowMaterial);
    addChild(wallRight);

    float doorWallW = 10.0f * 1.41f;
    float doorW = 9.0f;
    float doorH = 25.0f;

    WallWithDoor* door4 = new WallWithDoor(
        doorWallW, wallH, depth, doorW, doorH
    );

    door4->position = { -15.0f, wallH / 2.0f, 15.0f };
    door4->rotation.y = glm::radians(-45.0f);

    door4->setWallMaterial(wallMaterial);
    door4->setDoorMaterial(doorMaterial);
    addChild(door4);

}
