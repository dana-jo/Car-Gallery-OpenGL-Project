#pragma once
#include "../core/SceneNode.h"
#include "../utils/Mesh.h"
#include <array>

enum class CylinderPart { Side = 0, Top = 1, Bottom = 2 };

class Material;

class Cylinder : public SceneNode
{
public:
    Cylinder(float r, float h, int segments);
    ~Cylinder() = default;

    void setPartMaterial(CylinderPart part, Material* material);
    void setMaterial(Material* material);

    virtual void draw(class Shader& shader) override;

private:
    Mesh* mesh = nullptr;
    unsigned int sideIndexCount = 0;
    unsigned int topIndexCount = 0;
    unsigned int bottomIndexCount = 0;
    std::array<Material*, 3> partMaterials = { nullptr, nullptr, nullptr };
};
