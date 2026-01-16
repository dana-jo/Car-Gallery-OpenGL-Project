#pragma once
#include "SceneNode.h"
#include <glm/glm.hpp>

enum class LightType {
    Directional,
    Point,
    Spot
};

class LightNode : public SceneNode {
public:
    LightType type;

    // common
    glm::vec3 ambient{ 0.1f };
    glm::vec3 diffuse{ 1.0f };
    glm::vec3 specular{ 1.0f };

    // attenuation (point / spot)
    float constant = 1.0f;
    float linear = 0.045f;
    float quadratic = 0.008f;

    // spotlight only
    glm::vec3 direction{ 0, -1, 0 };
    float cutOff = 0.0f;
    float outerCutOff = 0.0f;

    bool enabled = true;

    LightNode(LightType t) : type(t) {}
};
