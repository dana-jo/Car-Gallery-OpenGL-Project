#include "scene/CartoonCar.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/constants.hpp>

CartoonCar::CartoonCar(float scale, Material* faceMat)
{
    // ===============================
    // Base dimensions (REAL size)
    // ===============================
    float bodyW = 7.0f;
    float bodyH = 7.0f;
    float bodyD = 7.0f;

    float wheelR = 1.0f;
    float wheelW = 0.7f;

    // ===============================
    // Materials
    // ===============================
    Texture* texCard = new Texture("assets/textures/cardboard-texture.jpg");
    Texture* texCardSide = new Texture("assets/textures/sideCartooncar.png");
    Material* matCard = new Material(texCard);
    Material* matCardSide = new Material(texCardSide);

    // ===============================
    // Body
    // ===============================
    body = new Box(
        bodyW * scale,
        bodyH * scale,
        bodyD * scale
    );
    body->setMaterial(matCard);
	body->setFaceMaterial(BoxFace::Back, matCardSide);
	body->setFaceMaterial(BoxFace::Front, matCardSide);
    body->setFaceMaterial(BoxFace::Right, faceMat);
    
    addChild(body);

    // ===============================
    // Wheels
    // ===============================
    for (int i = 0; i < 4; ++i)
    {
        wheels[i] = new Cylinder(
            wheelR * scale,
            wheelW * scale,
            20
        );

        float sx = (i < 2) ? -0.35f : 0.35f;
        float sz = (i % 2 == 0) ? 0.5f : -0.5f;

        wheels[i]->position = {
            sx * bodyW * scale,
            (-bodyH * 0.5f - wheelR * 0.9f + 1.f) * scale,
            sz * bodyD * scale
        };

        wheels[i]->rotation = {
            glm::half_pi<float>(),
            0.0f,
            0.0f
        };

        wheels[i]->setMaterial(matCard);
        addChild(wheels[i]);
    }
}
