#include "scene/Room4.h"
#include "WallWithHole.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/WallWithDoor.h"
#include "../../ZZZ.h"
#include "Model.h"

Room4::Room4(float gWidth, float gHeight, float gDepth, float g)
{
    // Wall and door dimensions
    float wallH = gHeight;
    float wallW = 30.0f;
    float depth = 0.2f;

    float winW = 20.0f;
    float winH = wallH * 0.75f;

    float doorW = 9.0f;
    float doorH = wallH * 0.625f;
    float doorWallW = 10.0f * 1.41f;

    // Materials
    Material* wallMaterial = new Material(new Texture("assets/textures/white.png"), { 2,2 });
    Material* windowMaterial = new Material(new Texture("assets/textures/window1.png"), { 1,1 });
    Material* doorMaterial = new Material(new Texture("assets/textures/door_frame.png"), { 1,1 });

    // Walls
    WallWithHole* wallFront = new WallWithHole(wallW, wallH, depth, winW, winH);
    wallFront->position = { 5.0f, wallH / 2.0f, 20.0f };
    wallFront->setWallMaterial(wallMaterial);
    wallFront->setWindowMaterial(wallMaterial);
    addChild(wallFront);

    WallWithHole* wallRight = new WallWithHole(wallW, wallH, depth, winW, winH);
    wallRight->position = { -20.0f, wallH / 2.0f, -5.0f };
    wallRight->rotation.y = glm::radians(90.0f);
    wallRight->setWallMaterial(wallMaterial);
    wallRight->setWindowMaterial(windowMaterial);
    addChild(wallRight);

    // Door
    WallWithDoor* door4 = new WallWithDoor(doorWallW, wallH, depth, doorW, doorH);
    door4->position = { -15.0f, wallH / 2.0f, 15.0f };
    door4->rotation.y = glm::radians(-45.0f);
    door4->setWallMaterial(wallMaterial);
    door4->setDoorMaterial(doorMaterial);
    addChild(door4);

	Model* mrBean = new Model("assets/models/mr_bean_rigged/scene.gltf");
	mrBean->scale = { 7.0f, 7.0f, 7.0f };
	mrBean->position = { -14.0f, 0.0f, -15.0f };
	mrBean->rotation.y = glm::radians(30.0f);
	addChild(mrBean);

    Box* shelf = new Box(
        18.0f,   // width
        0.5f,    // thickness
        6.0f     // depth (how much it sticks out)
    );

    float shelfDepth = 6.0f;

    shelf->position = {
        5.0f,
        wallH * 0.30f,
        20.0f - (shelfDepth / 2.0f) - 0.01f
    };

    shelf->setMaterial(wallMaterial);
    addChild(shelf);

    Model* miniCar = new Model("assets/models/british_leyland_mini/scene.gltf");
    miniCar->scale = { 0.9f, 0.9f, 0.9f };

    miniCar->position = {
        -6.0f,   
        -1.0f,   
        0.0f    
    };

    miniCar->rotation.x = glm::radians(-90.0f);
	miniCar->rotation.z = glm::radians(-55.0f);

    // Attach to shelf, not room
    shelf->addChild(miniCar);
    car = new ZZZ();
    car->position = { 0, 4, 4 };
    car->scale = {3, 3, 3};
    car->rotation.y = 180;
    addChild(car);

}
