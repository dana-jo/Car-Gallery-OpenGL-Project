#include "scene/World.h"
#include "scene/Gallery.h"
#include "scene/Surroundings.h"
#include "scene/TayoBus.h"
#include "scene/Ambulance.h"


World::World()
{
       
    TayoBus* bus = new TayoBus();
    bus->position = { 0.0f, 0.0f, 0.0f };
	addChild(bus);

    /*gallery = new Gallery();
    gallery->position = { 0.0f, 0.0f, 0.0f };

    addChild(gallery);*/

    //surroundings = new Surroundings();
    //surroundings->position = { 0.0f, -0.1f, 0.0f }; // slightly below gallery floor

    //addChild(surroundings);
}

World::~World() = default;
