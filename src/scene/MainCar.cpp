#include "scene/MainCar.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"

MainCar::MainCar()
{
    // simple car body
    body = new Box(1.4f, 0.4f, 0.7f); // main body
    body->position = { 0.0f, 0.25f, 0.0f };
    addChild(body);

    // cabin
    Box* cabin = new Box(0.8f, 0.35f, 0.6f);
    cabin->position = { 0.0f, 0.55f, 0.0f };
    addChild(cabin);

    // wheels: two axles * two wheels
    float wheelR = 0.18f;
    for (int i = 0; i < 4; ++i) {
        wheels[i] = new Cylinder(wheelR, 0.1f, 16);
        float sx = (i < 2) ? -0.5f : 0.5f;
        float sz = (i % 2 == 0) ? -0.3f : 0.3f;
        wheels[i]->position = { sx, wheelR * 0.5f, sz };
        addChild(wheels[i]);
    }
}

MainCar::~MainCar() = default;

void MainCar::setMaterial(Material* mat)
{
    material = mat;
    body->setMaterial(mat);
    // wheels can have their own dark material later
}
