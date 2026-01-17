#include "scene/GalleryShell.h"
#include "../objects/Box.h"
#include "../graphics/Texture.h"
#include "../graphics/Material.h"
#include "../core/LightNode.h"
#include "scene/Room1.h"
#include "scene/Room2.h"
#include "scene/Room3.h"
#include "scene/Room4.h"
#include "objects/WallWithHole.h"
#include "objects/WallWithDoor.h"

class Room1;

GalleryShell::GalleryShell(
    float width,
    float depth,
    float height,
    float t
) {
	this->t = t;

    // ---------- TEXTURES ----------
    Texture* wallTex = new Texture("assets/textures/white.png");
    Texture* windowTex = new Texture("assets/textures/window1.png");
	Texture* doorTex = new Texture("assets/textures/door_frame.png");
	Texture* floorTex = new Texture("assets/textures/light-wooden-floor-background.jpg");


    // ---------- MATERIALS ----------
    wallMaterial = new Material(wallTex, { 2.0f, 2.0f });
    wallMaterial->shininess = 8.0f;

    windowMaterial = new Material(windowTex, { 1.0f, 1.0f });
    windowMaterial->shininess = 32.0f;

	doorMaterial = new Material(doorTex, { 1.0f, 1.0f });
	floorMaterial = new Material(floorTex, { 4.0f, 4.0f });

  
    float frontZ = 60.0f;
    float backZ = -60.0f;
    float sideX = 60.0f;

    // Front wall with door
    buildWallRow(frontZ, true, true);

    // Back wall (3 windows)
    buildWallRow(backZ, false, true);

    // Left wall (3 windows)
    buildWallRow(sideX, false, false);

    // Right wall (3 windows)
    buildWallRow(-sideX, false, false);

    // ---------- FLOOR ----------
    Box* floor = new Box(120.0f, t, 120.0f);   // width, thickness, depth
    floor->position = { 0.0f, t / 2.0f, 0.0f }; // slightly above y=0
    floor->setMaterial(floorMaterial);          // reuse wall material or make a floor material
    addChild(floor);

    // ---------- CEILING ----------
    Box* ceiling = new Box(120.0f, t, 120.0f);
    ceiling->position = { 0.0f, 40.0f + t / 2.0f, 0.0f }; // at top of gallery
    ceiling->setMaterial(wallMaterial);         // can use same material or a different one
    addChild(ceiling);

    // Add lights
    addGalleryLights(120.0f, 120.0f, 40.0f); // gallery width, depth, wall height

    // ---------- LIGHTS ----------
    float lightHeight = 40.0f - 0.5f; // slightly below ceiling
    float margin = 2.0f;              // distance from walls

    glm::vec3 lightPositions[] = {
        { -60.0f + margin, lightHeight, -60.0f + margin }, // front-left
        {  60.0f - margin, lightHeight, -60.0f + margin }, // front-right
        { -60.0f + margin, lightHeight,  60.0f - margin }, // back-left
        {  60.0f - margin, lightHeight,  60.0f - margin }, // back-right
    };

    for (auto& pos : lightPositions)
    {
        LightNode* light = new LightNode(LightType::Point);
        light->position = pos;

        // light color and intensity
        light->ambient = glm::vec3(0.1f);  // soft ambient
        light->diffuse = glm::vec3(1.0f);  // strong diffuse
        light->specular = glm::vec3(1.0f);  // bright specular

        addChild(light);
    }

	Room1* room1 = new Room1(120.0f, 120.0f, 40.0f, t);
    room1->position = {-40.0f, 0.0f, 40.0f};
	addChild(room1);

    Room2* r2 = new Room2(120.0f, 120.0f, 40.0f, t);
    r2->position = { 40.0f, 0.0f,  40.0f };
    addChild(r2);

    Room3* r3 = new Room3(120.0f, 120.0f, 40.0f, t);
    r3->position = { -40.0f, 0.0f, -40.0f };
    addChild(r3);

    Room4* r4 = new Room4(120.0f, 120.0f, 40.0f, t);
    r4->position = { 40.0f, 0.0f, -40.0f };
    addChild(r4);

    
}

void GalleryShell::buildWallRow(
    float pos,             // position along the main axis
    bool middleIsDoor,     // whether the middle wall is a door
    bool alongZ     // true = front/back wall, false = left/right wall
)
{
    float segW = 40.0f;
    float wallH = 40.0f;
    float holeW = 30.0f;
    float holeH = 30.0f;
    float doorW = 20.0f;
    float doorH = 30.0f;

    float y = wallH / 2.0f;

    // Determine rotation and axis
    glm::vec3 leftPos, midPos, rightPos;
    float segDepth = t;

    if (alongZ)
    {
        // Front/back walls along Z
        leftPos = { -segW, y, pos };
        midPos = { 0.0f, y, pos };
        rightPos = { segW, y, pos };
    }
    else
    {
        // Side walls along X (rotate 90°)
        leftPos = { pos, y, -segW };
        midPos = { pos, y, 0.0f };
        rightPos = { pos, y, segW };
    }

    // LEFT
    auto* left = new WallWithHole(segW, wallH, segDepth, holeW, holeH);
    left->position = leftPos;
    if (!alongZ) left->rotation.y = glm::radians(90.0f); // rotate side walls
    left->setWallMaterial(wallMaterial);
    left->setWindowMaterial(windowMaterial);
    addChild(left);

    // MIDDLE
    if (middleIsDoor)
    {
        auto* mid = new WallWithDoor(segW, wallH, segDepth, doorW, doorH);
        mid->position = midPos;
        if (!alongZ) mid->rotation.y = glm::radians(90.0f);
        mid->setWallMaterial(wallMaterial);
        mid->setDoorMaterial(doorMaterial);
        addChild(mid);
    }
    else
    {
        auto* mid = new WallWithHole(segW, wallH, segDepth, holeW, holeH);
        mid->position = midPos;
        if (!alongZ) mid->rotation.y = glm::radians(90.0f);
        mid->setWallMaterial(wallMaterial);
        mid->setWindowMaterial(windowMaterial);
        addChild(mid);
    }

    // RIGHT
    auto* right = new WallWithHole(segW, wallH, segDepth, holeW, holeH);
    right->position = rightPos;
    if (!alongZ) right->rotation.y = glm::radians(90.0f);
    right->setWallMaterial(wallMaterial);
    right->setWindowMaterial(windowMaterial);
    addChild(right);
}

void GalleryShell::addGalleryLights(float galleryWidth, float galleryDepth, float wallHeight)
{
    float lightY = wallHeight - 1;  // just below 40 wall height
    float seg[] = { -40.0f, 0.0f, 40.0f };

    glm::vec3 center = { 0.0f, 0.0f, 0.0f };

    // ---------- FRONT WALL ----------
    for (float x : seg)
    {
        auto* l = new LightNode(LightType::Spot);
        l->enabled = true;
        glm::vec3 pos = { x, lightY, 60.0f };
        setupSpotLight(l, pos, center - pos);
        addChild(l);
    }

    // ---------- BACK WALL ----------
    for (float x : seg)
    {
        auto* l = new LightNode(LightType::Spot);
		l->enabled = true;
        glm::vec3 pos = { x, lightY, -60.0f };
        setupSpotLight(l, pos, center - pos);
        addChild(l);
    }

    // ---------- LEFT WALL ----------
    for (float z : seg)
    {
        auto* l = new LightNode(LightType::Spot);
        l->enabled = true;
        glm::vec3 pos = { -60.0f, lightY, z };
        setupSpotLight(l, pos, center - pos);
        addChild(l);
    }

    // ---------- RIGHT WALL ----------
    for (float z : seg)
    {
        auto* l = new LightNode(LightType::Spot);
        l->enabled = true;
        glm::vec3 pos = { 60.0f, lightY, z };
        setupSpotLight(l, pos, center - pos);
        addChild(l);
    }
}

// ---------------- Helper to set common light properties ----------------
void GalleryShell::setLightProps(LightNode* light)
{
    light->ambient = glm::vec3(0.1f);  // soft ambient light
    light->diffuse = glm::vec3(1.0f);  // strong diffuse light
    light->specular = glm::vec3(1.0f);  // bright specular
}

void GalleryShell::setupSpotLight(
    LightNode* light,
    const glm::vec3& position,
    const glm::vec3& direction
)
{
    light->position = position;
    light->direction = glm::normalize(direction);

    light->ambient = glm::vec3(0.05f); // very subtle
    light->diffuse = glm::vec3(2.0f);
    light->specular = glm::vec3(1.0f);

    light->cutOff = glm::cos(glm::radians(25.0f));       // inner cone
    light->outerCutOff = glm::cos(glm::radians(35.0f)); // soft edge
}



    
//// ---------- LIGHTS ----------
//float lightHeight = 40.0f - 0.5f; // slightly below ceiling
//float margin = 2.0f;              // distance from walls
//
//glm::vec3 lightPositions[] = {
//    { -60.0f + margin, lightHeight, -60.0f + margin }, // front-left
//    {  60.0f - margin, lightHeight, -60.0f + margin }, // front-right
//    { -60.0f + margin, lightHeight,  60.0f - margin }, // back-left
//    {  60.0f - margin, lightHeight,  60.0f - margin }, // back-right
//};
//
//for (auto& pos : lightPositions)
//{
//    LightNode* light = new LightNode(LightType::Point);
//    light->position = pos;
//
//    // light color and intensity
//    light->ambient = glm::vec3(0.1f);  // soft ambient
//    light->diffuse = glm::vec3(1.0f);  // strong diffuse
//    light->specular = glm::vec3(1.0f);  // bright specular
//
//    addChild(light);
//
//    // ---------- WALL SPOTLIGHTS ----------
//    float wallLightHeight = 35.0f; // slightly below ceiling
//    float wallLightOffset = 5.0f;  // distance from wall edge
//    float wallLength = 120.0f;     // gallery width/depth
//    float wallSpacing = wallLength / 4.0f; // spacing between lights
//
//    // Spotlights on front/back walls along X
//    for (int i = 0; i < 3; ++i)
//    {
//        float xPos = -wallLength / 2 + wallSpacing * (i + 1);
//
//        // Front wall spotlight
//        LightNode* frontSpot = new LightNode(LightType::Spot);
//        frontSpot->position = { xPos, wallLightHeight, +60.0f }; // frontZ
//        frontSpot->direction = glm::vec3(0.0f, -1.0f, -0.5f);    // pointing downward & inward
//        frontSpot->ambient = glm::vec3(0.05f);
//        frontSpot->diffuse = glm::vec3(1.0f);
//        frontSpot->specular = glm::vec3(1.0f);
//        addChild(frontSpot);
//
//        // Back wall spotlight
//        LightNode* backSpot = new LightNode(LightType::Spot);
//        backSpot->position = { xPos, wallLightHeight, -60.0f }; // backZ
//        backSpot->direction = glm::vec3(0.0f, -1.0f, 0.5f);     // downward & inward
//        backSpot->ambient = glm::vec3(0.05f);
//        backSpot->diffuse = glm::vec3(1.0f);
//        backSpot->specular = glm::vec3(1.0f);
//        addChild(backSpot);
//    }
//
//    // Spotlights on left/right walls along Z
//    for (int i = 0; i < 3; ++i)
//    {
//        float zPos = -wallLength / 2 + wallSpacing * (i + 1);
//
//        // Left wall spotlight
//        LightNode* leftSpot = new LightNode(LightType::Spot);
//        leftSpot->position = { -60.0f, wallLightHeight, zPos }; // sideX
//        leftSpot->direction = glm::vec3(0.5f, -1.0f, 0.0f);     // downward & inward
//        leftSpot->ambient = glm::vec3(0.05f);
//        leftSpot->diffuse = glm::vec3(1.0f);
//        leftSpot->specular = glm::vec3(1.0f);
//        addChild(leftSpot);
//
//        // Right wall spotlight
//        LightNode* rightSpot = new LightNode(LightType::Spot);
//        rightSpot->position = { 60.0f, wallLightHeight, zPos }; // sideX
//        rightSpot->direction = glm::vec3(-0.5f, -1.0f, 0.0f);   // downward & inward
//        rightSpot->ambient = glm::vec3(0.05f);
//        rightSpot->diffuse = glm::vec3(1.0f);
//        rightSpot->specular = glm::vec3(1.0f);
//        addChild(rightSpot);
//    }
//
//}
