#include "MeshNode.h"
#include "../core/Shader.h"

MeshNode::MeshNode(Mesh* m, Material* mat,
    const glm::vec3& colliderSize,
    const glm::vec3& colliderCenter)
    : mesh(m), material(mat)
{
    if (material && material->transparent)
        transparent = true;
    //collider = new BoxCollider(colliderSize, colliderCenter);
    localMin = colliderCenter - colliderSize * 0.5f;
    localMax = colliderCenter + colliderSize * 0.5f;
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