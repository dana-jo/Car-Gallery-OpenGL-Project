#pragma once
#include "../core/SceneNode.h"
#include "../graphics/Material.h"
#include "scene/Room4.h"

class LightNode;

class GalleryShell : public SceneNode {
public:
    GalleryShell(
        float width,
        float depth,
        float height,
        float wallThickness
    );

	~GalleryShell() override = default;
    void buildWallRow(float pos, bool middleIsDoor, bool alongZ = true);
    void setLightProps(LightNode* light);
    void addGalleryLights(float galleryWidth, float galleryDepth, float wallHeight);
    void setupSpotLight(LightNode* light, const glm::vec3& position, const glm::vec3& direction);

	float t; // wall thickness

    Room4* r4 = nullptr;

private:
    Material* wallMaterial = nullptr;
    Material* floorMaterial = nullptr;
    Material* ceilingMaterial = nullptr;
    Material* doorMaterial = nullptr;
    Material* windowMaterial = nullptr;
    
};
