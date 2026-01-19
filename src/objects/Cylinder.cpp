#include "Cylinder.h"
#include "../utils/Mesh.h"
#include "../core/Shader.h"
#include "../graphics/Material.h"
#include <cmath>
#include <glad/glad.h>

Cylinder::Cylinder(float r, float h, int segments)
    : radius(r), height(h)
{
    collider = new BoxCollider({ 2*r,h, 2*r });

    float half = h / 2.0f;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // SIDE
    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * 2.0f * 3.1415926f;
        float x = cos(angle) * r;
        float z = sin(angle) * r;

        vertices.push_back({ {x,-half,z},{x,0,z},{(float)i / segments,0} });
        vertices.push_back({ {x, half,z},{x,0,z},{(float)i / segments,1} });
    }

    for (unsigned int i = 0; i < (unsigned int)segments * 2; i += 2)
    {
        indices.insert(indices.end(), {
            i, i + 1, i + 2,
            i + 1, i + 3, i + 2
            });
    }

    sideIndexCount = indices.size();

    // TOP
    unsigned int topCenter = vertices.size();
    vertices.push_back({ {0, half, 0},{0,1,0},{0.5f,0.5f} });

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * 2.0f * 3.1415926f;
        vertices.push_back({
            {cos(angle) * r,half,sin(angle) * r},
            {0,1,0},
            {(cos(angle) + 1) / 2,(sin(angle) + 1) / 2}
            });
    }

    for (int i = 0; i < segments; i++)
    {
        indices.insert(indices.end(), {
            topCenter,
            topCenter + i + 1,
            topCenter + i + 2
            });
    }

    topIndexCount = indices.size() - sideIndexCount;

    // BOTTOM
    unsigned int bottomCenter = vertices.size();
    vertices.push_back({ {0,-half,0},{0,-1,0},{0.5f,0.5f} });

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * 2.0f * 3.1415926f;
        vertices.push_back({
            {cos(angle) * r,-half,sin(angle) * r},
            {0,-1,0},
            {(cos(angle) + 1) / 2,(sin(angle) + 1) / 2}
            });
    }

    for (int i = 0; i < segments; i++)
    {
        indices.insert(indices.end(), {
            bottomCenter,
            bottomCenter + i + 2,
            bottomCenter + i + 1
            });
    }

    bottomIndexCount = indices.size() - sideIndexCount - topIndexCount;

    mesh = new Mesh(vertices, indices);
    mesh->setup();
}

void Cylinder::setPartMaterial(CylinderPart part, Material* material)
{
    partMaterials[(int)part] = material;
    // update transparency flag of node if any material has transparency
    if (material && material->transparent) this->transparent = true;
    else {
        bool anyTransparent = false;
        for (auto m : partMaterials) if (m && m->transparent) anyTransparent = true;
        this->transparent = anyTransparent;
    }
}

void Cylinder::setMaterial(Material* material)
{
    for (auto& m : partMaterials) m = material;
    if (material) this->transparent = material->transparent;
}

void Cylinder::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());

    glBindVertexArray(mesh->VAO);

    unsigned int offset = 0;

    // Side
    if (partMaterials[0]) partMaterials[0]->bind(shader, 0);
    glDrawElements(GL_TRIANGLES, sideIndexCount, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
    offset += sideIndexCount;

    // Top
    if (partMaterials[1]) partMaterials[1]->bind(shader, 0);
    glDrawElements(GL_TRIANGLES, topIndexCount, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
    offset += topIndexCount;

    // Bottom
    if (partMaterials[2]) partMaterials[2]->bind(shader, 0);
    glDrawElements(GL_TRIANGLES, bottomIndexCount, GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));

    glBindVertexArray(0);

    SceneNode::draw(shader); // draw children
}
