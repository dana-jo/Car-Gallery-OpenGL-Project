#include "scene/Room2.h"
#include "WallWithHole.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/WallWithDoor.h"
#include "objects/Cylinder.h"
#include <Model.h>
#include "FamilyCar.h"

Room2::Room2(float gWidth, float gHeight, float gDepth, float g)
{
    Texture* wallTex = new Texture("assets/textures/white.png");
    Texture* windowTex = new Texture("assets/textures/window1.png");
    Texture* doorTex = new Texture("assets/textures/door_frame.png");
    Texture* floorTex = new Texture("assets/textures/light-wooden-floor-background.jpg");

    Material* wallMaterial = new Material(wallTex, { 2.0f, 2.0f });
    wallMaterial->shininess = 8.0f;

    Material* windowMaterial = new Material(windowTex, { 1.0f, 1.0f });
    windowMaterial->shininess = 32.0f;

    Material* doorMaterial = new Material(doorTex, { 1.0f, 1.0f });
    Material* floorMaterial = new Material(floorTex, { 4.0f, 4.0f });

    float wallH = gHeight;
    float wallW = 30.0f;
    float depth = 0.2f;

    float doorH = wallH * 0.625f;
    float doorW = 9.0f;
    float doorWallW = 10.0f * 1.41f;
    float winH = wallH * 0.75f;
    float winW = 20.0f;

    // Back wall (faces -Z)
    WallWithHole* wallBack = new WallWithHole(wallW, wallH, depth, winW, winH);
    wallBack->position = { +5.0f, wallH/2.0f, -20.0f };
    wallBack->setWallMaterial(wallMaterial);
    wallBack->setWindowMaterial(wallMaterial);
    addChild(wallBack);

    // Right wall (faces +X)
    WallWithHole* wallRight = new WallWithHole(wallW, wallH, depth, winW, winH);

    wallRight->position = { -20.0f, wallH/2.0f, 5.0f };
    wallRight->rotation.y = glm::radians(90.0f);

    wallRight->setWallMaterial(wallMaterial);
    wallRight->setWindowMaterial(windowMaterial);
    addChild(wallRight);

    WallWithDoor* door2 = new WallWithDoor(doorWallW, wallH, depth, doorW, doorH);
    door2->position = { -15.0f, wallH / 2.0f, -15.0f }; // <- use wallH/2, not doorH/2
    door2->rotation.y = glm::radians(-135.0f);
    door2->setWallMaterial(wallMaterial);
    door2->setDoorMaterial(doorMaterial);
    addChild(door2);

    /*Model* car2 = new Model("assets/cicada_retro_cartoon_car_gltf/scene.gltf");
    car2->scale = { 0.02f, 0.02f, 0.02f };
    car2->position = { 0.0f, 5.0f, 0.0f };
    car2->rotation.x = glm::radians(-90.0f);

    addChild(car2);*/

    float standRadius = 9.0f;
    float standHeight = 0.7f;


    

    FamilyCar* car = new FamilyCar();
    car->scale = { 0.7f, 0.7f, 0.7f };
    car->position = { -10.0f, standHeight, 8.0f };
    car->rotation.y = glm::radians(-150.0f);
    car->setCarMaterial();
	addChild(car);

	Model* carModel = new Model("assets/models/cicada_retro_cartoon_car_gltf/scene.gltf");
	carModel->scale = { 0.13f, 0.13f, 0.13f };
	carModel->position = { 5.0f, standHeight, 0.0f };
	carModel->rotation.x = glm::radians(-90.0f);
	carModel->rotation.z = glm::radians(-50.0f);
	addChild(carModel);

    Cylinder* carStand = new Cylinder(standRadius, standHeight, 32);


    // Center under car
    carStand->position = {
        car->position.x,
        standHeight / 2.0f,
        car->position.z
    };

    // Optional: slightly darker than walls
    Material* standMaterial = new Material(wallTex, { 1.0f, 1.0f });
    standMaterial->shininess = 16.0f;
    carStand->setMaterial(standMaterial);

    addChild(carStand);

    Model* table = new Model("assets/models/wooden_table_02_1k/wooden_table_02_1k.fbx");
    table->scale = { 8.0f, 8.0f, 6.0f };
    table->position = { 10.0f, 0.0f, -16.0f };
    table->rotation.x = glm::radians(-90.0f);
    //table->rotation.y = glm::radians(25.0f);
    addChild(table);

	Model* vase = new Model("assets/models/ceramic_vase_01_1k/ceramic_vase_01_1k.fbx");
	vase->scale = { 1.5f, 1.5f, 1.5f };
	vase->position = { 0.0f, 0.0f, 0.8f };
	table->addChild(vase);

	Model* frame = new Model("assets/models/hanging_picture_frame_02_1k/hanging_picture_frame_02_1k.fbx");
	frame->scale = { 14.0f, 14.0f, 14.0f };
	frame->position = { 3.0f, wallH * 0.6f, -19.7f };
	frame->rotation.y = glm::radians(180.0f);
	frame->rotation.x = glm::radians(-90.0f);
	addChild(frame);

	Model* chandelier = new Model("assets/models/Chandelier_03_1k/Chandelier_03_1k.fbx");
    chandelier->scale = { 8.0f, 8.0f, 8.0f };
    chandelier->position = { 0.0f, wallH - 2.0f, 0.0f };
    chandelier->rotation.x = glm::radians(-90.0f);
	addChild(chandelier);

}
