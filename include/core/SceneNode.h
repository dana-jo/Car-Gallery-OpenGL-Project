#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../core/BoxCollider.h"

class Shader;

class SceneNode
{
public:
    SceneNode();
    virtual ~SceneNode();

    // Transform (LOCAL)
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    // Hierarchy
    SceneNode* parent = nullptr;
    std::vector<SceneNode*> children;

    BoxCollider* collider = nullptr; // add this
    bool ignoreCollision = false;         // new: skip this node in collision checks

    // Mark if this node should be drawn as transparent (used by renderer)
    bool transparent = false;

    // Core functions
    void addChild(SceneNode* child);
    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix() const;

    virtual void update(float dt, const glm::vec3& cameraPos);
    virtual void draw(class Shader& shader);
    void collectColliders(std::vector<SceneNode*>& out);


    // helper: returns world position extracted from world matrix
    glm::vec3 getWorldPosition() const;
    glm::vec3 getForward() const;

};
