#include "scene/Surroundings.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"

Street::Street(float w, float d)
{
    ground = new Box(w, 0.05f, d);
    addChild(ground);
}
Street::~Street() = default;

Building::Building(float w, float h, float d)
{
    body = new Box(w, h, d);
    addChild(body);
}
Building::~Building() = default;

Tree::Tree(float trunkH, float trunkR, float foliageSize)
{
    trunk = new Cylinder(trunkR, trunkH, 12);
    trunk->position = { 0.0f, trunkH * 0.5f, 0.0f };
    addChild(trunk);

    foliage = new Box(foliageSize, foliageSize, foliageSize);
    foliage->position = { 0.0f, trunkH + foliageSize * 0.5f, 0.0f };
    addChild(foliage);
}
Tree::~Tree() = default;

Surroundings::Surroundings()
{
    // street under the gallery
    Street* street = new Street(40.0f, 20.0f);
    street->position = { 0.0f, -0.2f, 0.0f };
    addChild(street);

    // add couple of buildings
    Building* b1 = new Building(4.0f, 6.0f, 3.0f);
    b1->position = { -10.0f, 0.0f, -4.0f };
    addChild(b1);

    Building* b2 = new Building(6.0f, 8.0f, 4.0f);
    b2->position = { 12.0f, 0.0f, 3.0f };
    addChild(b2);

    // trees
    for (int i = 0; i < 6; ++i) {
        Tree* t = new Tree(1.0f + 0.2f * i, 0.1f + 0.02f * i, 0.8f);
        t->position = { -8.0f + i * 3.0f, 0.0f, -8.0f };
        addChild(t);
    }
}
Surroundings::~Surroundings() = default;
