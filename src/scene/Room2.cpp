#include "scene/Room2.h"
#include "WallWithHole.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/WallWithDoor.h"
#include <Model.h>

Room2::Room2(float gWidth, float gHeight, float gDepth, float g)
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

    // Back wall (faces -Z)
    auto* wallBack = new WallWithHole(wallW, wallH, depth, 20, 30);
    wallBack->position = { +5.0f, 20.0f, -20.0f };
    wallBack->setWallMaterial(wallMaterial);
    wallBack->setWindowMaterial(windowMaterial);
    addChild(wallBack);

    // Right wall (faces +X)
    auto* wallRight = new WallWithHole(wallW, wallH, depth, 20, 30);

    wallRight->position = { -20.0f, 20.0f, 5.0f };
    wallRight->rotation.y = glm::radians(90.0f);

    wallRight->setWallMaterial(wallMaterial);
    wallRight->setWindowMaterial(windowMaterial);
    addChild(wallRight);

    float doorWallW = 10.0f * 1.41f;
    float doorW = 9.0f;
    float doorH = 25.0f;

    WallWithDoor* door2 = new WallWithDoor(
        doorWallW, wallH, depth, doorW, doorH
    );

    // Centered between perpendicular walls
    door2->position = { -15.0f, wallH / 2.0f, -15.0f };

    // Rotate to face inward (towards gallery)
    door2->rotation.y = glm::radians(-135.0f);

    door2->setWallMaterial(wallMaterial);
    door2->setDoorMaterial(doorMaterial);
    addChild(door2);

    /*Model* car2 = new Model("assets/cicada_retro_cartoon_car_gltf/scene.gltf");
    car2->scale = { 0.02f, 0.02f, 0.02f };
    car2->position = { 0.0f, 5.0f, 0.0f };
    car2->rotation.x = glm::radians(-90.0f);

    addChild(car2);*/


}
