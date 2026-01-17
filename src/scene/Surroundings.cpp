#include "scene/Surroundings.h"
#include "objects/Box.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "objects/Model.h"

Surroundings::Surroundings(float gallerySize, float t)
{

	Texture* pavementTex = new Texture("assets/textures/modern-stone-wall.jpg");
	Texture* streetTex = new Texture("assets/textures/cracked-asphalt.jpg");

	Material* pavementMaterial1 = new Material(pavementTex, { 16.0f, 4.0f });
	Material* pavementMaterial2 = new Material(pavementTex, { 4.0f, 16.0f });
	Material* streetMaterial1 = new Material(streetTex, { 16.0f, 4.0f });
	Material* streetMaterial2 = new Material(streetTex, { 4.0f, 16.0f });

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    ///////////////THE SURROUNDINGS/////////////////////

    float galleryHalf = 60.0f;
    float pavementW = 15.0f;
    float y = t / 2.0f;

    float pavementThickness = 2.0f;
    float streetThickness = 0.6f;

    // FRONT pavement
    Box* pavFront = new Box(120.0f + pavementW * 2, pavementThickness, pavementW);
    pavFront->position = { 0.0f, y, galleryHalf + pavementW / 2.0f };
    pavFront->setMaterial(pavementMaterial1);
    addChild(pavFront);

    // BACK pavement
    Box* pavBack = new Box(120.0f + pavementW * 2, pavementThickness, pavementW);
    pavBack->position = { 0.0f, y, -(galleryHalf + pavementW / 2.0f) };
    pavBack->setMaterial(pavementMaterial1);
    addChild(pavBack);

    // LEFT pavement
    Box* pavLeft = new Box(pavementW, pavementThickness, 120.0f);
    pavLeft->position = { -(galleryHalf + pavementW / 2.0f), y, 0.0f };
    pavLeft->setMaterial(pavementMaterial2);
    addChild(pavLeft);

    // RIGHT pavement
    Box* pavRight = new Box(pavementW, pavementThickness, 120.0f);
    pavRight->position = { galleryHalf + pavementW / 2.0f, y, 0.0f };
    pavRight->setMaterial(pavementMaterial2);
    addChild(pavRight);

    float streetW = 110.0f;
    float streetOffset = galleryHalf + pavementW + streetW / 2.0f;

    // FRONT street
    Box* streetFront = new Box(150.0f, streetThickness, streetW);
    streetFront->position = { 0.0f, y, streetOffset };
    streetFront->setMaterial(streetMaterial1);
    addChild(streetFront);

    // BACK street
    Box* streetBack = new Box(150.0f, streetThickness, streetW);
    streetBack->position = { 0.0f, y, -streetOffset };
    streetBack->setMaterial(streetMaterial1);
    addChild(streetBack);

    // LEFT street
    Box* streetLeft = new Box(streetW, streetThickness, 150.0f + streetW * 2);
    streetLeft->position = { -streetOffset, y, 0.0f };
    streetLeft->setMaterial(streetMaterial2);
    addChild(streetLeft);

    // RIGHT street
    Box* streetRight = new Box(streetW, streetThickness, 150.0f + streetW * 2);
    streetRight->position = { streetOffset, y, 0.0f };
    streetRight->setMaterial(streetMaterial2);
    addChild(streetRight);

    Texture* buildingTex = new Texture("assets/textures/white-building.jpg");
    Material* buildingMat = new Material(buildingTex, { 2.0f, 4.0f });


    // Distance where buildings start (outside the street)
    float buildingOffset = galleryHalf + pavementW + streetW -50.0f;

    // ---------- FRONT BUILDINGS ----------
    Box* bF1 = new Box(18.0f, 35.0f, 16.0f);
    bF1->position = { -45.0f, 35.0f / 2.0f, buildingOffset };
    bF1->setMaterial(buildingMat);
    addChild(bF1);

    Box* bF2 = new Box(22.0f, 50.0f, 20.0f);
    bF2->position = { -10.0f, 50.0f / 2.0f, buildingOffset + 4.0f };
    bF2->setMaterial(buildingMat);
    addChild(bF2);

    Box* bF3 = new Box(16.0f, 28.0f, 14.0f);
    bF3->position = { 25.0f, 28.0f / 2.0f, buildingOffset - 3.0f };
    bF3->setMaterial(buildingMat);
    addChild(bF3);

    Box* bF4 = new Box(26.0f, 60.0f, 22.0f);
    bF4->position = { 55.0f, 60.0f / 2.0f, buildingOffset + 6.0f };
    bF4->setMaterial(buildingMat);
    addChild(bF4);

    // ---------- FRONT EXTRA BUILDING ----------
    Box* bF5 = new Box(32.0f, 75.0f, 26.0f);
    bF5->position = { 85.0f, 75.0f / 2.0f, buildingOffset + 10.0f };
    bF5->setMaterial(buildingMat);
    addChild(bF5);


    // ---------- BACK BUILDINGS ----------
    Box* bB1 = new Box(20.0f, 40.0f, 18.0f);
    bB1->position = { -50.0f, 40.0f / 2.0f, -buildingOffset };
    bB1->setMaterial(buildingMat);
    addChild(bB1);

    Box* bB2 = new Box(15.0f, 25.0f, 14.0f);
    bB2->position = { -15.0f, 25.0f / 2.0f, -buildingOffset - 5.0f };
    bB2->setMaterial(buildingMat);
    addChild(bB2);

    Box* bB3 = new Box(24.0f, 55.0f, 20.0f);
    bB3->position = { 20.0f, 55.0f / 2.0f, -buildingOffset + 3.0f };
    bB3->setMaterial(buildingMat);
    addChild(bB3);

    Box* bB4 = new Box(18.0f, 33.0f, 16.0f);
    bB4->position = { 48.0f, 33.0f / 2.0f, -buildingOffset };
    bB4->setMaterial(buildingMat);
    addChild(bB4);

    // ---------- BACK EXTRA BUILDING ----------
    Box* bB5 = new Box(30.0f, 70.0f, 24.0f);
    bB5->position = { -85.0f, 70.0f / 2.0f, -buildingOffset - 8.0f };
    bB5->setMaterial(buildingMat);
    addChild(bB5);



    // ---------- RIGHT BUILDINGS ----------
    Box* bR1 = new Box(16.0f, 30.0f, 18.0f);
    bR1->position = { buildingOffset, 30.0f / 2.0f, -45.0f };
    bR1->setMaterial(buildingMat);
    addChild(bR1);

    Box* bR2 = new Box(22.0f, 55.0f, 22.0f);
    bR2->position = { buildingOffset + 4.0f, 55.0f / 2.0f, -1.0f };
    bR2->setMaterial(buildingMat);
    addChild(bR2);

    Box* bR3 = new Box(14.0f, 24.0f, 16.0f);
    bR3->position = { buildingOffset - 3.0f, 24.0f / 2.0f, 20.0f };
    bR3->setMaterial(buildingMat);
    addChild(bR3);

    Box* bR4 = new Box(26.0f, 65.0f, 24.0f);
    bR4->position = { buildingOffset + 6.0f, 65.0f / 2.0f, 50.0f };
    bR4->setMaterial(buildingMat);
    addChild(bR4);

    // ---------- RIGHT EXTRA BUILDING ----------
    Box* bR5 = new Box(28.0f, 80.0f, 26.0f);
    bR5->position = { buildingOffset + 10.0f, 80.0f / 2.0f, -85.0f };
    bR5->setMaterial(buildingMat);
    addChild(bR5);



    // ---------- LEFT BUILDINGS ----------
    Box* bL1 = new Box(20.0f, 45.0f, 18.0f);
    bL1->position = { -buildingOffset, 45.0f / 2.0f, -50.0f };
    bL1->setMaterial(buildingMat);
    addChild(bL1);

    Box* bL2 = new Box(14.0f, 26.0f, 14.0f);
    bL2->position = { -buildingOffset - 4.0f, 26.0f / 2.0f, -15.0f };
    bL2->setMaterial(buildingMat);
    addChild(bL2);

    Box* bL3 = new Box(24.0f, 58.0f, 22.0f);
    bL3->position = { -buildingOffset + 2.0f, 58.0f / 2.0f, 18.0f };
    bL3->setMaterial(buildingMat);
    addChild(bL3);

    Box* bL4 = new Box(18.0f, 34.0f, 16.0f);
    bL4->position = { -buildingOffset, 34.0f / 2.0f, 52.0f };
    bL4->setMaterial(buildingMat);
    addChild(bL4);

    // ---------- LEFT EXTRA BUILDING ----------
    Box* bL5 = new Box(34.0f, 85.0f, 28.0f);
    bL5->position = { -buildingOffset - 12.0f, 85.0f / 2.0f, 85.0f };
    bL5->setMaterial(buildingMat);
    addChild(bL5);

    // ---------- FRONT TREES ----------
    Model* tF1 = new Model("assets/pine/scrubPine.obj");
    tF1->position = { -30.0f, 0.0f, streetOffset - 7.0f };
    tF1->rotation.y = glm::radians(15.0f);
    tF1->scale = { 0.03f, 0.03f, 0.03f };
    addChild(tF1);

    Model* tF2 = new Model("assets/pine/scrubPine.obj");
    tF2->position = { 30.0f, 0.0f, streetOffset - 8.0f };
    tF2->rotation.y = glm::radians(-20.0f);
    tF2->scale = { 0.027f, 0.027f, 0.027f };
    addChild(tF2);

    Model* tF3 = new Model("assets/pine/scrubPine.obj");
    tF3->position = { 90.0f, 0.0f, streetOffset };
    tF3->scale = { 0.035f, 0.035f, 0.035f };
    addChild(tF3);

    // ---------- BACK TREES ----------
    Model* tB1 = new Model("assets/pine/scrubPine.obj");
    tB1->position = { -30.0f, 0.0f, -streetOffset + 2.0f };
    tB1->scale = { 0.03f, 0.03f, 0.03f };
    addChild(tB1);

    Model* tB2 = new Model("assets/pine/scrubPine.obj");
    tB2->position = { 30.0f, 0.0f, -streetOffset + 11.0f };
    tB2->scale = { 0.027f, 0.027f, 0.027f };
    addChild(tB2);

    Model* tB3 = new Model("assets/pine/scrubPine.obj");
    tB3->position = { -70.0f, 0.0f, -streetOffset + 7.0f };
    tB3->scale = { 0.035f, 0.035f, 0.035f };
    addChild(tB3);

    // ---------- LEFT TREES ----------
    Model* tL1 = new Model("assets/pine/scrubPine.obj");
    tL1->position = { -streetOffset + 5.0f, 0.0f, -30.0f };
    tL1->scale = { 0.03f, 0.03f, 0.03f };
    addChild(tL1);

    Model* tL2 = new Model("assets/pine/scrubPine.obj");
    tL2->position = { -streetOffset + 10.0f, 0.0f, 30.0f };
    tL2->scale = { 0.027f, 0.027f, 0.027f };
    addChild(tL2);

    Model* tL3 = new Model("assets/pine/scrubPine.obj");
    tL3->position = { -streetOffset + 4.0f, 0.0f, 70.0f };
    tL3->scale = { 0.035f, 0.035f, 0.035f };
    addChild(tL3);

    // ---------- RIGHT TREES ----------
    Model* tR1 = new Model("assets/pine/scrubPine.obj");
    tR1->position = { streetOffset - 5.0f, 0.0f, -30.0f };
    tR1->scale = { 0.03f, 0.03f, 0.03f };
    addChild(tR1);

    Model* tR2 = new Model("assets/pine/scrubPine.obj");
    tR2->position = { streetOffset - 8.0f, 0.0f, 30.0f };
    tR2->scale = { 0.027f, 0.027f, 0.027f };
    addChild(tR2);

    Model* tR3 = new Model("assets/pine/scrubPine.obj");
    tR3->position = { streetOffset - 4.0f, 0.0f, -70.0f };
    tR3->scale = { 0.035f, 0.035f, 0.035f };
    addChild(tR3);


}

Surroundings::~Surroundings() = default;
