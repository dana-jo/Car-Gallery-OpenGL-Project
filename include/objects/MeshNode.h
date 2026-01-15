#pragma once
#include "../core/SceneNode.h"
#include "../utils/Mesh.h"
#include "../graphics/Material.h"

class MeshNode : public SceneNode
{
public:
    MeshNode(Mesh* mesh, Material* material);
    ~MeshNode();

    void draw(Shader& shader) override;

private:
    Mesh* mesh;
    Material* material;
};
