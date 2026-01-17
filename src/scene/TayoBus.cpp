#include "scene/TayoBus.h"
#include "../objects/Box.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/constants.hpp>

TayoBus::TayoBus()
{
    // create car body
    body = new Box(.9f, 0.5f, 0.5f);
    body->position = { 0.0f, 0.25f, 0.0f };
    addChild(body);

    // load textures
    Texture* texRight = new Texture("assets/textures/tayo_face.jpg");
    Texture* texBack = new Texture("assets/textures/tayo_left.png");
    Texture* texLeft = new Texture("assets/textures/tayo_back.jpg");
    Texture* texFront = new Texture("assets/textures/tayo_right.png");
    Texture* texTop = new Texture("assets/textures/red.png");
    //Texture* texTop = new Texture("assets/textures/formulaCar_top.jpg");
    //Texture* texBottom = new Texture("assets/textures/green.png"); // REMOVE THIS

    // create materials
    Material* matFront = new Material(texFront);
    Material* matBack = new Material(texBack);
    Material* matLeft = new Material(texLeft);
    Material* matRight = new Material(texRight);
    Material* matTop = new Material(texTop);
    //matBottom = new Material(texBottom);

    // assign materials to faces
    body->setFaceMaterial(BoxFace::Front, matFront);
    body->setFaceMaterial(BoxFace::Back, matBack);
    body->setFaceMaterial(BoxFace::Left, matLeft);
    body->setFaceMaterial(BoxFace::Right, matRight);
    body->setFaceMaterial(BoxFace::Top, matTop);
    //body->setFaceMaterial(BoxFace::Bottom, matBottom);

    // wheels
    float wheelR = 0.1f;
    float wheelW = 0.05f;

    for (int i = 0; i < 4; ++i)
    {
        wheels[i] = new Cylinder(wheelR, wheelW, 20);

        float sx = (i < 2) ? -0.245f : 0.165f;     // left / right
        float sz = (i % 2 == 0) ? 0.25f : -0.25f;  // front / back

        wheels[i]->position = { sx, wheelR * 0.45f, sz };

        // rotate cylinder so it looks like a wheel
        wheels[i]->rotation = { glm::half_pi<float>() ,0.0f,  0.0f};

        wheels[i]->setMaterial(new Material(new Texture("assets/textures/black.png")));

        addChild(wheels[i]);
    }
}
