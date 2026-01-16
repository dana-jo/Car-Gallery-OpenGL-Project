#pragma once
#include "../core/SceneNode.h"
#include "scene/Gallery.h" // Add this include to resolve incomplete type
#include "objects/Object.h"


class Surroundings;
class Gallery;

class World : public Object {
public:
    World();
    ~World() override;

    Gallery* gallery = nullptr;
    Surroundings* surroundings = nullptr;
};

