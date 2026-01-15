#include "MeshNode.h"
#include "../core/Shader.h"

MeshNode::MeshNode(Mesh* m, Material* mat)
    : mesh(m), material(mat)
{
    if (material && material->transparent)
        transparent = true;
}

MeshNode::~MeshNode()
{
    delete mesh;
    delete material;
}

void MeshNode::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());

    if (material)
        material->bind(shader, 0);

    if (mesh)
        mesh->draw();

    SceneNode::draw(shader);
}
