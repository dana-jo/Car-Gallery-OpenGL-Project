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
#include <Model.h>

class Room1;

GalleryShell::GalleryShell(
    float width,
    float depth,
    float wallHeight,
    float t  // wall/floor thickness
) {
    this->t = t;
    this->wallHeight = wallHeight; // store dynamic wall height

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

    float frontZ = depth / 2.0f;
    float backZ = -depth / 2.0f;
    float sideX = width / 2.0f;

    // ---------- WALL ROWS ----------
    buildWallRow(frontZ, true, true);   // front wall with door
    buildWallRow(backZ, false, true);   // back wall with windows
    buildWallRow(sideX, false, false);  // left wall
    buildWallRow(-sideX, false, false); // right wall

    // ---------- FLOOR ----------

    Box* floor = new Box(width, t, depth);
    floor->position = { 0.0f, t / 2.0f, 0.0f };
    floor->setMaterial(floorMaterial);
    addChild(floor);
	floor->collider = new BoxCollider({ 120.0f, glm::max(t,10.f), 120.0f });
	//floor->ignoreCollision = true; // false should be

    // ---------- CEILING ----------
    Box* ceiling = new Box(width, t, depth);
    ceiling->position = { 0.0f, wallHeight + t / 2.0f, 0.0f };
    ceiling->setMaterial(wallMaterial);
    addChild(ceiling);

    // ---------- LIGHTS ----------
    addGalleryLights(width, depth, wallHeight);

    // ---------- ROOMS ----------
    Room1* room1 = new Room1(width, wallHeight, depth, t);
    room1->position = { -width / 3.0f, 0.0f, depth / 3.0f };
    addChild(room1);

    //Room2* r2 = new Room2(width, wallHeight, depth, t);
    //r2->position = { width / 3.0f, 0.0f, depth / 3.0f };
    //addChild(r2);

    //Room3* r3 = new Room3(width, wallHeight, depth, t);
    //r3->position = { -width / 3.0f, 0.0f, -depth / 3.0f };
    //addChild(r3);

    r4 = new Room4(width, wallHeight, depth, t);
    r4->position = { width / 3.0f, 0.0f, -depth / 3.0f };
    addChild(r4);

	Model* securityCam = new Model("assets/models/security_camera_01_1k/security_camera_01_1k.fbx");
	securityCam->scale = { 8.0f, 8.0f, 8.0f };
	securityCam->rotation.z = glm::radians(180.0f);
    securityCam->rotation.y = glm::radians(180.0f);
	securityCam->rotation.x = glm::radians(100.0f);
	securityCam->position = { 0.0f, wallHeight - 3.0f, -depth / 2.0f + 1.0f };
	addChild(securityCam);

	Model* couch = new Model("assets/models/sofa/3D_sofa_2-TuO.fbx");
	couch->scale = { 13.f, 13.0f, 13.0f };
	couch->position = { 50.0f,  0.0f, -1.0f};
	couch->rotation.y = glm::radians(-180.0f);
	couch->rotation.x = glm::radians(90.0f);
	couch->rotation.z = glm::radians(90.0f);
	addChild(couch);

	Model* plant = new Model("assets/models/potted_plant_01_1k/potted_plant_01_1k.fbx");
	plant->scale = { 12.f, 12.0f, 12.0f };
	plant->position = { 52.0f, 0.0f, 16.0f };
	plant->rotation.x = glm::radians(-90.0f);
	addChild(plant);

   
    LightNode* couchLight = new LightNode(LightType::Point);
    couchLight->position = {
        couch->position.x + 5.0,
        5.0f,                      
        couch->position.z -3.0f
    };

    // Soft, warm light
    couchLight->ambient = glm::vec3(0.05f);
    couchLight->diffuse = glm::vec3(0.8f, 0.75f, 0.7f); // warm tone
    couchLight->specular = glm::vec3(0.3f);

    // Attenuation for softness
    couchLight->constant = 1.0f;
    couchLight->linear = 0.09f;
    couchLight->quadratic = 0.032f;

    addChild(couchLight);

	Model* chandelier = new Model("assets/models/ceiling_lamp_flower_style/scene.gltf");
	chandelier->scale = { 0.08f, 0.08f, 0.08f };
	chandelier->position = { 0.0f, wallHeight - 14.0f, 0.0f };
	chandelier->rotation.x = glm::radians(-90.0f);
	addChild(chandelier);

	LightNode* chandelierLight = new LightNode(LightType::Point);
    chandelierLight->position = {
        chandelier->position.x,
        chandelier->position.y,
        chandelier->position.z
	};
	chandelierLight->ambient = glm::vec3(0.5f);
	chandelierLight->diffuse = glm::vec3(1.5f, 1.4f, 1.2f); // warm white
	chandelierLight->specular = glm::vec3(1.0f);
	// Attenuation
	chandelierLight->constant = 1.0f;
	chandelierLight->linear = 0.14f;
	chandelierLight->quadratic = 0.07f;
	addChild(chandelierLight);

	Model* armchair = new Model("assets/models/armchair/3D_armchair_11.fbx");
	armchair->scale = { 15.f, 15.0f, 15.0f };
	armchair->position = { -50.0f, 0.0f, -10.0f };
	armchair->rotation.z = glm::radians(45.0f);
	armchair->rotation.x = glm::radians(-90.0f);
	addChild(armchair);

	LightNode* armchairLight = new LightNode(LightType::Point);
    armchairLight->position = {
        armchair->position.x - 3.0f,
        5.0f,
        armchair->position.z + 3.0f
    };
    // Soft, warm light
    armchairLight->ambient = glm::vec3(0.05f);
    armchairLight->diffuse = glm::vec3(0.8f, 0.75f, 0.7f); // warm tone
    armchairLight->specular = glm::vec3(0.3f);
    // Attenuation for softness
    armchairLight->constant = 1.0f;
    armchairLight->linear = 0.09f;
    armchairLight->quadratic = 0.032f;
	addChild(armchairLight);

}


void GalleryShell::buildWallRow(
    float pos,
    bool middleIsDoor,
    bool alongZ
) {
    float segW = 40.0f;
    float holeW = 30.0f;
    float holeH = wallHeight * 0.75f; // scale window height
    float doorW = 20.0f;
    float doorH = wallHeight * 0.85f; // scale door height

    float y = wallHeight / 2.0f;

    glm::vec3 leftPos, midPos, rightPos;
    float segDepth = t;

    if (alongZ) {
        leftPos = { -segW, y, pos };
        midPos = { 0.0f, y, pos };
        rightPos = { segW, y, pos };
    }
    else {
        leftPos = { pos, y, -segW };
        midPos = { pos, y, 0.0f };
        rightPos = { pos, y, segW };
    }

    // LEFT
    auto* left = new WallWithHole(segW, wallHeight, segDepth, holeW, holeH);
    left->position = leftPos;
    if (!alongZ) left->rotation.y = glm::radians(90.0f);
    left->setWallMaterial(wallMaterial);
    left->setWindowMaterial(windowMaterial);
    addChild(left);

    // MIDDLE
    if (middleIsDoor) {
        auto* mid = new WallWithDoor(segW, wallHeight, segDepth, doorW, doorH);
        mid->position = midPos;
        if (!alongZ) mid->rotation.y = glm::radians(90.0f);
        mid->setWallMaterial(wallMaterial);
        mid->setDoorMaterial(doorMaterial);
        addChild(mid);
    }
    else {
        auto* mid = new WallWithHole(segW, wallHeight, segDepth, holeW, holeH);
        mid->position = midPos;
        if (!alongZ) mid->rotation.y = glm::radians(90.0f);
        mid->setWallMaterial(wallMaterial);
        mid->setWindowMaterial(windowMaterial);
        addChild(mid);
    }

    // RIGHT
    auto* right = new WallWithHole(segW, wallHeight, segDepth, holeW, holeH);
    right->position = rightPos;
    if (!alongZ) right->rotation.y = glm::radians(90.0f);
    right->setWallMaterial(wallMaterial);
    right->setWindowMaterial(windowMaterial);
    addChild(right);
}


void GalleryShell::addGalleryLights(float galleryWidth, float galleryDepth, float wallHeight) {
    float lightY = wallHeight - 0.5f; // just below ceiling
    float seg[] = { -40.0f, 0.0f, 40.0f };
    glm::vec3 center = { 0.0f, 0.0f, 0.0f };

    // FRONT WALL
    for (float x : seg) {
        LightNode* l = new LightNode(LightType::Spot);
        setupSpotLight(l, { x, lightY, galleryDepth / 2.0f }, center - glm::vec3(x, lightY, galleryDepth / 2.0f));
        addChild(l);
    }

    // BACK WALL
    for (float x : seg) {
        LightNode* l = new LightNode(LightType::Spot);
        setupSpotLight(l, { x, lightY, -galleryDepth / 2.0f }, center - glm::vec3(x, lightY, -galleryDepth / 2.0f));
        addChild(l);
    }

    // LEFT WALL
    for (float z : seg) {
        LightNode* l = new LightNode(LightType::Spot);
        setupSpotLight(l, { -galleryWidth / 2.0f, lightY, z }, center - glm::vec3(-galleryWidth / 2.0f, lightY, z));
        addChild(l);
    }

    // RIGHT WALL
    for (float z : seg) {
        LightNode* l = new LightNode(LightType::Spot);
        setupSpotLight(l, { galleryWidth / 2.0f, lightY, z }, center - glm::vec3(galleryWidth / 2.0f, lightY, z));
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
