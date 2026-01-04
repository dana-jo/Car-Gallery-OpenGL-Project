#pragma once
#include "Object.h"

#include <array>

enum class CylinderPart
{
    SIDE = 0,
    TOP = 1,
    BOTTOM = 2
};

class Cylinder : public Object
{
public:

    Cylinder(float radius, float height, int segments);

	void setPartTexture(CylinderPart part, Texture* texture);
	void setTexture(Texture* texture);

    void draw(Shader& shader) override;

private:

	std::array<Texture*, 3> partTextures{};
    int sideIndexCount = 0;
    int topIndexCount = 0;
    int bottomIndexCount = 0;
};
