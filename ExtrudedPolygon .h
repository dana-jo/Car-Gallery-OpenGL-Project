#pragma once
#include "../objects/Object.h"
#include "../graphics/Material.h"
#include "../utils/Mesh.h"
#include <glm/glm.hpp>
#include <vector>

enum class PrismFace
{
    Front,
    Back,
    Side0,
    Side1,
    Side2,
    Side3,
    Side4,
    Side5
};


class ExtrudedPolygon : public SceneNode
{
public:
    ExtrudedPolygon(const std::vector<glm::vec2>& shape, float depth);

    void setFrontMaterial(Material* m);
    void setBackMaterial(Material* m);
    void setSideMaterial(size_t edgeIndex, Material* m);

    void draw(Shader& shader) override;

private:
    std::vector<glm::vec2> polygon2D;
    float depth;

    Mesh* frontMesh = nullptr;
    Mesh* backMesh = nullptr;
    std::vector<Mesh*> sideMeshes;

    Material* frontMat = nullptr;
    Material* backMat = nullptr;
    std::vector<Material*> sideMats;

    void build();
};
