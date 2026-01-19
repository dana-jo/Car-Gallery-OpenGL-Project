#pragma once
#include "../core/SceneNode.h"
#include <Model.h>

class OiiaioooooiaiCat : public SceneNode
{
public:
    OiiaioooooiaiCat();

    void update(float dt, const glm::vec3& cameraPos) override;

private:
    Model* catModel;
    float rotationSpeed;
};
