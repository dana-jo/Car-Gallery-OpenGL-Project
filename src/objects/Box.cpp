#include "Box.h"
#include "../utils/Mesh.h"
#include "../core/Shader.h"
#include "../graphics/Material.h"
#include <glad/glad.h>
#include "../core/BoxCollider.h"   //


Box::Box(float w, float h, float d)
    : width(w), height(h), depth(d)
{
    scale = { 1,1,1 };

    collider = new BoxCollider({ w, h, d });
 
    float x = w / 2;
    float y = h / 2;
    float z = d / 2;

    std::vector<Vertex> vertices = {
        // FRONT
        {{-x,-y, z},{0,0,1},{0,0}},
        {{ x,-y, z},{0,0,1},{1,0}},
        {{ x, y, z},{0,0,1},{1,1}},
        {{-x, y, z},{0,0,1},{0,1}},
        // BACK
        {{ x,-y,-z},{0,0,-1},{0,0}},
        {{-x,-y,-z},{0,0,-1},{1,0}},
        {{-x, y,-z},{0,0,-1},{1,1}},
        {{ x, y,-z},{0,0,-1},{0,1}},
        // LEFT
        {{-x,-y,-z},{-1,0,0},{0,0}},
        {{-x,-y, z},{-1,0,0},{1,0}},
        {{-x, y, z},{-1,0,0},{1,1}},
        {{-x, y,-z},{-1,0,0},{0,1}},
        // RIGHT
        {{ x,-y, z},{1,0,0},{0,0}},
        {{ x,-y,-z},{1,0,0},{1,0}},
        {{ x, y,-z},{1,0,0},{1,1}},
        {{ x, y, z},{1,0,0},{0,1}},
        // TOP
        {{-x, y, z},{0,1,0},{0,0}},
        {{ x, y, z},{0,1,0},{1,0}},
        {{ x, y,-z},{0,1,0},{1,1}},
        {{-x, y,-z},{0,1,0},{0,1}},
        // BOTTOM
        {{-x,-y,-z},{0,-1,0},{0,0}},
        {{ x,-y,-z},{0,-1,0},{1,0}},
        {{ x,-y, z},{0,-1,0},{1,1}},
        {{-x,-y, z},{0,-1,0},{0,1}},
    };

    std::vector<unsigned int> indices;
    for (int i = 0; i < 6; i++)
    {
        unsigned int offset = i * 4;
        indices.insert(indices.end(), {
            offset, offset + 1, offset + 2,
            offset + 2, offset + 3, offset
            });
    }

    mesh = new Mesh(vertices, indices);
    mesh->setup();
}

void Box::setFaceMaterial(BoxFace face, Material* material)
{
    int idx = static_cast<int>(face);
    faceMaterials[idx] = material;
    if (material) {
        // update node transparency if any face material is transparent
        if (material->transparent) this->transparent = true;
    }
    else {
        // if material removed, recompute transparency across faces
        bool anyTransparent = false;
        for (auto m : faceMaterials) if (m && m->transparent) anyTransparent = true;
        this->transparent = anyTransparent;
    }
}

void Box::setMaterial(Material* material)
{
    for (int i = 0; i < 6; ++i) {
        faceMaterials[i] = material;
    }
    if (material) this->transparent = material->transparent;
}

void Box::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());

    glBindVertexArray(mesh->VAO);

    for (int face = 0; face < 6; face++)
    {
        Material* mat = faceMaterials[face];
        if (mat) {
            mat->bind(shader, 0);
        }
        glDrawElements(
            GL_TRIANGLES,
            indicesPerFace,
            GL_UNSIGNED_INT,
            (void*)(face * indicesPerFace * sizeof(unsigned int))
        );
    }

    glBindVertexArray(0);
    SceneNode::draw(shader); // draw children
}
