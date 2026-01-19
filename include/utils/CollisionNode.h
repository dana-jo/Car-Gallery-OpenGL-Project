#pragma once
#include "SceneNode.h"
#include <glm/glm.hpp>

struct AABB
{
    glm::vec3 min;
    glm::vec3 max;

    bool intersects(const AABB& other) const
    {
        return (min.x <= other.max.x && max.x >= other.min.x) &&
            (min.y <= other.max.y && max.y >= other.min.y) &&
            (min.z <= other.max.z && max.z >= other.min.z);
    }
};

class CollisionNode : public SceneNode
{
public:
    AABB localAABB; // relative to this node's position

    AABB getWorldAABB() const
    {
        glm::vec3 worldPos = getWorldPosition();
        return { worldPos + localAABB.min, worldPos + localAABB.max };
    }

    bool checkCollision(const CollisionNode* other) const
    {
        return getWorldAABB().intersects(other->getWorldAABB());
    }
};
