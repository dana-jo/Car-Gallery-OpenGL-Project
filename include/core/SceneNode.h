#pragma once
#include <glm/glm.hpp>
#include <vector>

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

    // Core functions
    void addChild(SceneNode* child);
    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix() const;

    virtual void update() {}
    virtual void draw(class Shader& shader);
};
