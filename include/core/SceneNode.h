#pragma once
#include <glm/glm.hpp>
#include <vector>

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

    // Mark if this node should be drawn as transparent (used by renderer)
    bool transparent = false;

    // Core functions
    void addChild(SceneNode* child);
    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix() const;

    virtual void update() {}
    virtual void draw(class Shader& shader);

    // helper: returns world position extracted from world matrix
    glm::vec3 getWorldPosition() const;
    glm::vec3 getForward() const;
};
