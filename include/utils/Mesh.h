#pragma once
#include <vector>
#include <glad/glad.h>

struct Vertex
{
    float position[3];
    float normal[3];
    float texCoords[2];
};

class Mesh
{
public:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh();
    ~Mesh();
    Mesh(const std::vector<Vertex>& verts,
        const std::vector<unsigned int>& inds);

    void setup();
    void draw();
};
