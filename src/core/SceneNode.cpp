#include "../core/SceneNode.h"
#include <glm/gtc/matrix_transform.hpp>

SceneNode::SceneNode()
{
    position = { 0,0,0 };
    rotation = { 0,0,0 };
    scale = { 1,1,1 };
}

SceneNode::~SceneNode()
{
    for (SceneNode* child : children)
        delete child;
}

void SceneNode::addChild(SceneNode* child)
{
    child->parent = this;
    children.push_back(child);
}

glm::mat4 SceneNode::getLocalMatrix() const
{
    glm::mat4 m(1.0f);
    m = glm::translate(m, position);

    m = glm::rotate(m, rotation.x, { 1,0,0 });
    m = glm::rotate(m, rotation.y, { 0,1,0 });
    m = glm::rotate(m, rotation.z, { 0,0,1 });

    m = glm::scale(m, scale);
    return m;
}

glm::mat4 SceneNode::getWorldMatrix() const
{
    if (parent)
        return parent->getWorldMatrix() * getLocalMatrix();

    return getLocalMatrix();
}

void SceneNode::draw(Shader& shader)
{
    for (SceneNode* child : children)
        child->draw(shader);
}
