#include "../scene/FirstAidKit.h"
#include "../objects/Box.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"
#include <glm/gtc/matrix_transform.hpp>

FirstAidKit::FirstAidKit(float w, float h, float d)
{
    // --------- Materials / Textures (like FamilyCar) ----------
    matFront = new Material(new Texture("assets/textures/props/firstaid/kit_front.png"), { 1,1 });
    matBack = new Material(new Texture("assets/textures/props/firstaid/kit_side.png"), { 1,1 });
    matLeft = new Material(new Texture("assets/textures/props/firstaid/kit_side.png"), { 1,1 });
    matRight = new Material(new Texture("assets/textures/props/firstaid/kit_side.png"), { 1,1 });
    matTop = new Material(new Texture("assets/textures/props/firstaid/kit_top.png"), { 1,1 });
    matBottom = new Material(new Texture("assets/textures/props/firstaid/kit_bottom.png"), { 1,1 });


    // optional shininess
    matFront->shininess = 16.0f;

    // --------- Geometry ----------
    body = new Box(w, h, d);
    addChild(body);

    // apply materials
    setKitMaterial();
}

void FirstAidKit::setKitMaterial()
{
    if (!body) return;

    body->setFaceMaterial(BoxFace::Front, matFront);
    body->setFaceMaterial(BoxFace::Back, matBack);
    body->setFaceMaterial(BoxFace::Left, matLeft);
    body->setFaceMaterial(BoxFace::Right, matRight);
    body->setFaceMaterial(BoxFace::Top, matTop);
    body->setFaceMaterial(BoxFace::Bottom, matBottom);
}
