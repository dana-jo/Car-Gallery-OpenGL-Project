#include "ExtrudedPolygon .h"
#include "src/objects/Polygon.cpp"


ExtrudedPolygon::ExtrudedPolygon(
    const std::vector<glm::vec2>& shape,
    float d
) : polygon2D(shape), depth(d)
{
    sideMats.resize(shape.size(), nullptr);
    build();
}

void ExtrudedPolygon::build()
{
    float zF = depth * 0.5f;
    float zB = -depth * 0.5f;

    auto indices = earClip(polygon2D);

    // ---------- FRONT ----------
    {
        std::vector<Vertex> v;
        std::vector<unsigned int> i;

        for (auto& p : polygon2D)
            v.push_back({ {p.x, p.y, zF}, {0,0,1}, {0,0} });

        i = indices;

        frontMesh = new Mesh(v, i);
        frontMesh->setup();
    }

    // ---------- BACK ----------
    {
        std::vector<Vertex> v;
        std::vector<unsigned int> i;

        for (auto& p : polygon2D)
            v.push_back({ {p.x, p.y, zB}, {0,0,-1}, {0,0} });

        for (size_t k = 0; k < indices.size(); k += 3)
        {
            i.push_back(indices[k]);
            i.push_back(indices[k + 2]);
            i.push_back(indices[k + 1]);
        }

        backMesh = new Mesh(v, i);
        backMesh->setup();
    }

    // ---------- SIDES ----------
    for (size_t e = 0; e < polygon2D.size(); e++)
    {
        size_t n = (e + 1) % polygon2D.size();

        glm::vec2 a = polygon2D[e];
        glm::vec2 b = polygon2D[n];

        glm::vec3 normal = glm::normalize(glm::vec3(
            b.y - a.y,
            -(b.x - a.x),
            0.0f
        ));

        std::vector<Vertex> v = {
            {{a.x, a.y, zF}, normal, {0,0}},
            {{b.x, b.y, zF}, normal, {1,0}},
            {{b.x, b.y, zB}, normal, {1,1}},
            {{a.x, a.y, zB}, normal, {0,1}}
        };

        std::vector<unsigned int> i = {
            0,1,2,
            2,3,0
        };

        Mesh* m = new Mesh(v, i);
        m->setup();
        sideMeshes.push_back(m);
    }
}

void ExtrudedPolygon::setFrontMaterial(Material* m) { frontMat = m; }
void ExtrudedPolygon::setBackMaterial(Material* m) { backMat = m; }

void ExtrudedPolygon::setSideMaterial(size_t edge, Material* m)
{
    if (edge < sideMats.size())
        sideMats[edge] = m;
}

void ExtrudedPolygon::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());

    if (frontMat && frontMesh)
    {
        frontMat->bind(shader, 0);
        frontMesh->draw();
    }

    if (backMat && backMesh)
    {
        backMat->bind(shader, 0);
        backMesh->draw();
    }

    for (size_t i = 0; i < sideMeshes.size(); i++)
    {
        if (sideMats[i])
            sideMats[i]->bind(shader, 0);

        sideMeshes[i]->draw();
    }

    SceneNode::draw(shader);
}
