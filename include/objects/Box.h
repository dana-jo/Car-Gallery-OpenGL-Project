#pragma once
#include "../core/SceneNode.h"
#include "../utils/Mesh.h"
#include <array>

enum class BoxFace
{
    Front = 0, Back = 1, Left = 2, Right = 3, Top = 4, Bottom = 5
};

class Material;

class Box : public SceneNode
{
public:
    Box(float w, float h, float d);
    ~Box() = default;

    void setFaceMaterial(BoxFace face, Material* material);
    void setMaterial(Material* material); // set same material for all faces

    virtual void draw(class Shader& shader) override;

private:
    float width, height, depth;
    Mesh* mesh = nullptr;
    std::array<Material*, 6> faceMaterials = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    unsigned int indicesPerFace = 6;
};
