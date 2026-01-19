#pragma once
#include "RoomBase.h"
#include "../graphics/Material.h"
#include "../../ZZZ.h"

class Room4 : public RoomBase
{
public:
    Room4(float width, float depth, float height, float wallThickness);
    ZZZ* car = nullptr;

};
