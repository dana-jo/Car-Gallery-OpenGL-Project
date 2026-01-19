#include "scene/World.h"
#include "scene/Gallery.h"
#include "scene/Surroundings.h"
#include "scene/TayoBus.h"
#include "scene/Ambulance.h"


World::World()
{

    gallery = new Gallery();
    gallery->position = { 0.0f, 0.0f, 0.0f };

    addChild(gallery);

    //surroundings = new Surroundings(120.0f, 0.3f);
    //surroundings->position = { 0.0f, -0.1f, 0.0f }; // slightly below gallery floor

    //addChild(surroundings);
}

World::~World() = default;
