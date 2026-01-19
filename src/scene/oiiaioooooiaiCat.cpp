#include "scene/OiiaioooooiaiCat.h"
#include <glm/gtc/constants.hpp>
#include <AudioSystem.h>

OiiaioooooiaiCat::OiiaioooooiaiCat()
{
    rotationSpeed = glm::radians(90.0f);

    catModel = new Model("assets/models/oiiaioooooiai_cat/scene.gltf");
    catModel->scale = { 0.05f, 0.05f, 0.05f };
    catModel->position = { 0.0f, 0.0f, 0.0f };

    addChild(catModel);
}

void OiiaioooooiaiCat::update(float dt, const glm::vec3& cameraPos)
{
    glm::vec3 catWorldPosition = getWorldPosition();
    float dist = glm::distance(catWorldPosition, cameraPos);

    if (dist < 10.0f)
    {
        rotation.y += rotationSpeed * dt;
        if(!isRotating) AudioSystem::playMusic("assets/audios/oiia-oiia-spinning-cat.wav", true);

		isRotating = true;
    }
    else
    {
		isRotating = false;
		AudioSystem::stopMusic();
    }


    SceneNode::update(dt, cameraPos);
}
