#include "../utils/Mesh.h"
#include <glad/glad.h>
#include <iostream>

Mesh::Mesh()
{
    VAO = VBO = EBO = 0;
}

Mesh::Mesh(const std::vector<Vertex>& verts,
    const std::vector<unsigned int>& inds)
{
    vertices = verts;
    indices = inds;
}

void Mesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );

    // position (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, position)
    );

    // normal (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, normal)
    );

    // texCoords (location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, texCoords)
    );

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(
        GL_TRIANGLES,
        static_cast<unsigned int>(indices.size()),
        GL_UNSIGNED_INT,
        nullptr
    );
    glBindVertexArray(0);

    std::cout << "Drawing mesh, indices: " << indices.size() << std::endl;

}

//Mesh::~Mesh()
//{
//    if (EBO) glDeleteBuffers(1, &EBO);
//    if (VBO) glDeleteBuffers(1, &VBO);
//    if (VAO) glDeleteVertexArrays(1, &VAO);
//}

Mesh::~Mesh() = default;

