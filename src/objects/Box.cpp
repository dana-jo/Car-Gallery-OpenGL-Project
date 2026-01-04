#include <glad/glad.h>

#include "../objects/Box.h"
#include "../core/Shader.h"

Box::Box(float w, float h, float d)
{
    float x = w / 2;
    float y = h / 2;
    float z = d / 2;

    std::vector<Vertex> vertices = {
        // ---------- FRONT ----------
        {{-x,-y, z},{0,0,1},{0,0}},
        {{ x,-y, z},{0,0,1},{1,0}},
        {{ x, y, z},{0,0,1},{1,1}},
        {{-x, y, z},{0,0,1},{0,1}},

        // ---------- BACK ----------
        {{ x,-y,-z},{0,0,-1},{0,0}},
        {{-x,-y,-z},{0,0,-1},{1,0}},
        {{-x, y,-z},{0,0,-1},{1,1}},
        {{ x, y,-z},{0,0,-1},{0,1}},

        // ---------- LEFT ----------
        {{-x,-y,-z},{-1,0,0},{0,0}},
        {{-x,-y, z},{-1,0,0},{1,0}},
        {{-x, y, z},{-1,0,0},{1,1}},
        {{-x, y,-z},{-1,0,0},{0,1}},

        // ---------- RIGHT ----------
        {{ x,-y, z},{1,0,0},{0,0}},
        {{ x,-y,-z},{1,0,0},{1,0}},
        {{ x, y,-z},{1,0,0},{1,1}},
        {{ x, y, z},{1,0,0},{0,1}},

        // ---------- TOP ----------
        {{-x, y, z},{0,1,0},{0,0}},
        {{ x, y, z},{0,1,0},{1,0}},
        {{ x, y,-z},{0,1,0},{1,1}},
        {{-x, y,-z},{0,1,0},{0,1}},

        // ---------- BOTTOM ----------
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

void Box::setFaceTexture(BoxFace face, Texture* texture)
{
    faceTextures[static_cast<int>(face)] = texture;
}

void Box::setTexture(Texture* texture)
{
    for (auto& t : faceTextures)
        t = texture;
}

void Box::draw(Shader& shader)
{

    shader.setMat4("model", getWorldMatrix());

    glBindVertexArray(mesh->VAO);

    for (int face = 0; face < 6; face++)
    {

        if (faceTextures[face]) {

            //glActiveTexture(GL_TEXTURE0);
            faceTextures[face]->bind(0);
            // optional: ensure sampler uniform points to unit 0
            //shader.setInt("tex", 0);
        }

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            (void*)(face * 6 * sizeof(unsigned int))
        );
    }

	glBindVertexArray(0);

	SceneNode::draw(shader); // draw children
}


