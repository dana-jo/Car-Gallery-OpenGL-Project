#pragma once
#include "../objects/Object.h"
#include "objects/Polygon.h"
#include <glm/glm.hpp>
#include <vector>

class Material;

class Polygon : public SceneNode
{
public:
    Polygon(const std::vector<glm::vec2>& vertices2D, float depth);

    void setMaterial(Material* mat);
    void draw(Shader& shader) override;
    //void setPosition(const glm::vec3& pos) override;


private:
    Mesh* mesh;
	Material* material = nullptr;
    std::vector<glm::vec2> polygon2D;
	std::vector<unsigned int> indices2D;
    void buildMesh(const std::vector<glm::vec2>& v2, float depth);
	void triangulate();
	bool validate();
	
};
