#pragma once
#include "../core/SceneNode.h"
#include "scene/Room1.h"
#include "scene/Room2.h"
#include "scene/Room3.h"
#include "scene/Room4.h"

class Box;
class Material;
class GalleryShell;

class Gallery : public SceneNode {
public:
    Gallery();
    ~Gallery() override;

    GalleryShell* shell = nullptr;

};
