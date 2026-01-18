#pragma once
#include "SceneNode.h"
#include <glm/glm.hpp>

// Axis-Aligned Bounding Box collision, recursive for children
inline bool checkCollisionRecursive(SceneNode* a, SceneNode* b)
{
    if (!a || !b) return false;

    if (a->ignoreCollision || b->ignoreCollision)
        return false; 

    if (a->collider && b->collider)
    {
        glm::vec3 aPos = a->collider->getWorldPosition(a->getWorldPosition());
        glm::vec3 bPos = b->collider->getWorldPosition(b->getWorldPosition());

        glm::vec3 aMin = aPos - a->collider->size * 0.5f;
        glm::vec3 aMax = aPos + a->collider->size * 0.5f;
        glm::vec3 bMin = bPos - b->collider->size * 0.5f;
        glm::vec3 bMax = bPos + b->collider->size * 0.5f;

        if ((aMin.x <= bMax.x && aMax.x >= bMin.x) &&
            (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
            (aMin.z <= bMax.z && aMax.z >= bMin.z))
            return true;
    }

    // Recursively check all children of both nodes
    for (auto* childA : a->children)
        if (checkCollisionRecursive(childA, b)) return true;

    for (auto* childB : b->children)
        if (checkCollisionRecursive(a, childB)) return true;

    return false;
}
