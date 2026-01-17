#include "scene/Room1.h"
#include "../objects/Box.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "WallWithHole.h"
#include "WallWithDoor.h"

Room1::Room1(float gWidth, float gHeight, float gDepth, float g)
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

	float wallW, wallH, depth, winW, winH;
	
	wallW = 30.0f;
	wallH = 40.0f;
	depth = 0.2f;
	winW = 20.0f;
	winH = 30.0f;

	WallWithHole* wallBack = new WallWithHole(30.0f, 40.0f, 0.2f, 20.0f, 30.0f);

	wallBack->position = { -5.0f, 20.0f, -20.0f };
	wallBack->setWallMaterial(wallMaterial);
	wallBack->setWindowMaterial(windowMaterial);
	addChild(wallBack);


	WallWithHole* wallLeft = new WallWithHole(30.0f, 40.0f, 0.2f, 20.0f, 30.0f);

	wallLeft->position = { 20.0f, 20.0f, 5.0f };
	wallLeft->rotation.y = glm::radians(90.0f);

	wallLeft->setWallMaterial(wallMaterial);
	wallLeft->setWindowMaterial(windowMaterial);
	addChild(wallLeft);

	float doorWallW = 10.0f * 1.41f;
	float doorW = 9.0f;
	float doorH = 25.0f;


	WallWithDoor* door = new WallWithDoor(
		doorWallW, wallH, depth, doorW, doorH
	);

	// Door is centered between the two walls
	door->position = {15.0f, wallH / 2.0f, -15.0f };

	// Rotate to face inward (towards gallery)
	door->rotation.y = glm::radians(135.0f);

	door->setWallMaterial(wallMaterial);
	door->setDoorMaterial(doorMaterial);
	addChild(door);

}
