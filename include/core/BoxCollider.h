#pragma once
#include <glm/glm.hpp>

class BoxCollider
{
public:
    glm::vec3 offset; // local offset from node position
    glm::vec3 size;   // width, height, depth

    BoxCollider(const glm::vec3& size, const glm::vec3& offset = glm::vec3(0))
        : size(size), offset(offset) {
    }

    // World position given a SceneNode
    glm::vec3 getWorldPosition(const glm::vec3& nodePos) const
    {
        return nodePos + offset;
    }
};
