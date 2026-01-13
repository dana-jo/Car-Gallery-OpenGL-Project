#include "Polygon.h"
#include "../utils/Mesh.h"
#include "graphics/Material.h"
#include <stdexcept>

std::vector<unsigned int> earClip(const std::vector<glm::vec2>& poly);
float signedArea(const std::vector<glm::vec2>& poly);
bool pointInTriangle(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
bool isConvex(const glm::vec2& prev, const glm::vec2& curr, const glm::vec2& next);
float cross(const glm::vec2& a, const glm::vec2& b);

Polygon::Polygon(const std::vector<glm::vec2>& vertices2D, float depth)
{
    polygon2D = vertices2D;

    if (!validate())
        throw std::runtime_error("Invalid polygon");

    triangulate();          // fills indices2D
    buildMesh(polygon2D, depth);
}

void Polygon::buildMesh(const std::vector<glm::vec2>& v2, float depth)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float zFront = depth * 0.5f;
    float zBack  = -depth * 0.5f;

    unsigned int n = (unsigned int)v2.size();

    // --------------------
    // FRONT FACE
    // --------------------

    glm::vec2 min(FLT_MAX), max(-FLT_MAX);
    for (auto& p : v2)
    {
        min = glm::min(min, p);
        max = glm::max(max, p);
    }
    glm::vec2 size = max - min;

    for (auto& p : v2)
    {
        glm::vec2 uv = (p - min) / size;

        vertices.push_back({
            { p.x, p.y, zFront },
            { 0, 0, 1 },
            { uv.x, uv.y }
        });
    }

    // front face indices (fan)
    for (unsigned int i = 0; i < indices2D.size(); i += 3)
    {
        indices.push_back(indices2D[i]);
        indices.push_back(indices2D[i + 1]);
        indices.push_back(indices2D[i + 2]);
    }

    // --------------------
    // BACK FACE
    // --------------------
    unsigned int backOffset = vertices.size();

    for (auto& p : v2)
    {
        vertices.push_back({
            { p.x, p.y, zBack },
            { 0, 0, -1 },
            { 0, 0 }
            });
    }

    for (unsigned int i = 0; i < indices2D.size(); i += 3)
    {
        indices.push_back(backOffset + indices2D[i]);
        indices.push_back(backOffset + indices2D[i + 2]);
        indices.push_back(backOffset + indices2D[i + 1]);
    }


    // --------------------
    // SIDE FACES
    // --------------------
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int next = (i + 1) % n;

        glm::vec2 p0 = v2[i];
        glm::vec2 p1 = v2[next];

        glm::vec3 normal = glm::normalize(glm::vec3(
            p1.y - p0.y,
            -(p1.x - p0.x),
            0.0f
        ));

        unsigned int base = vertices.size();

        // quad vertices
        vertices.push_back({ {p0.x, p0.y, zFront}, {normal.x, normal.y, normal.z}, {0,0} });
        vertices.push_back({ {p1.x, p1.y, zFront}, {normal.x, normal.y, normal.z}, {1,0} });
        vertices.push_back({ {p1.x, p1.y, zBack }, {normal.x, normal.y, normal.z}, {1,1} });
        vertices.push_back({ {p0.x, p0.y, zBack }, {normal.x, normal.y, normal.z}, {0,1} });

        // two triangles
        indices.insert(indices.end(), {
            base, base + 1, base + 2,
            base + 2, base + 3, base
        });
    }

    mesh = new Mesh(vertices, indices);
    mesh->setup();
}

void Polygon::setMaterial(Material* mat)
{
    if (mat) {
        material = mat;
        transparent = mat->transparent;
    }
        
}

void Polygon::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());
    if (material)
        material->bind(shader, 0);

    if (mesh)
        mesh->draw();

	SceneNode::draw(shader); // draw children
}

void Polygon::triangulate()
{
    indices2D = earClip(polygon2D);
}

bool Polygon::validate()
{
    if (polygon2D.size() < 3)
        return false;

    //// Ensure CCW
    //if (signedArea(polygon2D) < 0)
    //    std::reverse(polygon2D.begin(), polygon2D.end());

    //// Self-intersection test
    //for (int i = 0; i < polygon2D.size(); i++)
    //{
    //    for (int j = i + 1; j < polygon2D.size(); j++)
    //    {
    //        // skip adjacent edges
    //        if (abs(i - j) <= 1 ||
    //            (i == 0 && j == polygon2D.size() - 1))
    //            continue;

    //        if (segmentsIntersect(
    //            polygon2D[i],
    //            polygon2D[(i + 1) % polygon2D.size()],
    //            polygon2D[j],
    //            polygon2D[(j + 1) % polygon2D.size()]))
    //            return false;
    //    }
    //}

    return true;
}

float signedArea(const std::vector<glm::vec2>& poly)
{
    float area = 0.0f;
    for (size_t i = 0; i < poly.size(); i++)
    {
        const auto& p = poly[i];
        const auto& q = poly[(i + 1) % poly.size()];
        area += (p.x * q.y - q.x * p.y);
    }
    return area * 0.5f;
}

float cross(const glm::vec2& a, const glm::vec2& b)
{
    return a.x * b.y - a.y * b.x;
}

bool isConvex(const glm::vec2& prev,
    const glm::vec2& curr,
    const glm::vec2& next)
{
    return cross(curr - prev, next - curr) > 0.0f;
}

bool pointInTriangle(const glm::vec2& p,
    const glm::vec2& a,
    const glm::vec2& b,
    const glm::vec2& c)
{
    float c1 = cross(b - a, p - a);
    float c2 = cross(c - b, p - b);
    float c3 = cross(a - c, p - c);

    return (c1 >= 0 && c2 >= 0 && c3 >= 0);
}

std::vector<unsigned int> earClip(const std::vector<glm::vec2>& poly)
{
    std::vector<unsigned int> indices;
    std::vector<unsigned int> V(poly.size());

    for (unsigned int i = 0; i < V.size(); i++)
        V[i] = i;

    while (V.size() > 3)
    {
        bool earFound = false;

        for (unsigned int i = 0; i < V.size(); i++)
        {
            unsigned int prev = V[(i + V.size() - 1) % V.size()];
            unsigned int curr = V[i];
            unsigned int next = V[(i + 1) % V.size()];

            const auto& a = poly[prev];
            const auto& b = poly[curr];
            const auto& c = poly[next];

            if (!isConvex(a, b, c))
                continue;

            bool containsPoint = false;
            for (unsigned int j = 0; j < V.size(); j++)
            {
                unsigned int vi = V[j];
                if (vi == prev || vi == curr || vi == next)
                    continue;

                if (pointInTriangle(poly[vi], a, b, c))
                {
                    containsPoint = true;
                    break;
                }
            }

            if (containsPoint)
                continue;

            // Ear found
            indices.push_back(prev);
            indices.push_back(curr);
            indices.push_back(next);

            V.erase(V.begin() + i);
            earFound = true;
            break;
        }

        if (!earFound)
            break; // invalid polygon
    }

    // Final triangle
    if (V.size() == 3)
    {
        indices.push_back(V[0]);
        indices.push_back(V[1]);
        indices.push_back(V[2]);
    }

    return indices;
}

