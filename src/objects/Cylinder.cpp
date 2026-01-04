#include "../objects/Cylinder.h"
#include <cmath>

Cylinder::Cylinder(float r, float h, int segments)
{
    float half = h / 2.0f;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // ---------- SIDE ----------
    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * 2.0f * 3.1415926f;
        float x = cos(angle) * r;
        float z = sin(angle) * r;

        vertices.push_back({ {x,-half,z},{x,0,z},{(float)i / segments,0} });
        vertices.push_back({ {x, half,z},{x,0,z},{(float)i / segments,1} });
    }

    for (unsigned int i = 0; i < segments * 2; i += 2)
    {
        indices.insert(indices.end(), {
            i, i + 1, i + 2,
            i + 1, i + 3, i + 2
            });
    }

    sideIndexCount = indices.size();

    // ---------- TOP ----------
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

    // ---------- BOTTOM ----------
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

    mesh =  new Mesh(vertices, indices);
    mesh->setup();
}

void Cylinder::setPartTexture(CylinderPart part, Texture* texture)
{
    partTextures[(int)part] = texture;
}

void Cylinder::setTexture(Texture* texture)
{
    for(auto& t : partTextures)
		t = texture;
}

void Cylinder::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());

    glBindVertexArray(mesh->VAO);

    unsigned int offset = 0;

    if (partTextures[0]) {

        //glActiveTexture(GL_TEXTURE0);

        partTextures[0]->bind(0);

        //shader.setInt("tex", 0);
    }

    glDrawElements(GL_TRIANGLES, sideIndexCount, GL_UNSIGNED_INT, 0);
    offset += sideIndexCount;

    if (partTextures[1]) {

        //glActiveTexture(GL_TEXTURE0);

        partTextures[1]->bind(0);

        //shader.setInt("tex", 0);
    }

    glDrawElements(
        GL_TRIANGLES,
        topIndexCount,
        GL_UNSIGNED_INT,
        (void*)(offset * sizeof(unsigned int))
    );

    offset += topIndexCount;

    if (partTextures[2]) {

        //glActiveTexture(GL_TEXTURE0);

        partTextures[2]->bind(0);

        //shader.setInt("tex", 0);
    }

    glDrawElements(
        GL_TRIANGLES,
        bottomIndexCount,
        GL_UNSIGNED_INT,
        (void*)(offset * sizeof(unsigned int))
    );

    glBindVertexArray(0);

	SceneNode::draw(shader); // draw children
}

