#include "Renderer.h"
#include "SceneNode.h"
#include <algorithm>
#include <glad/glad.h>
#include "../core/Shader.h"

void Renderer::submit(SceneNode* node)
{
    if (!node) return;

    if (node->transparent)
        transparentNodes.push_back(node);
    else
        opaqueNodes.push_back(node);

    // optionally submit children too (if you submit root nodes only you can skip)
    for (SceneNode* c : node->children)
        submit(c);
}

void Renderer::drawAll(const glm::vec3& cameraPos)
{
    // Draw opaque objects first
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    for (SceneNode* n : opaqueNodes)
    {
        n->draw(shader);
    }

    // Draw transparent objects: enable blending and disable depth writes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    // sort back-to-front by distance to camera
    std::sort(transparentNodes.begin(), transparentNodes.end(),
        [&](SceneNode* a, SceneNode* b)
        {
            float da = glm::length(cameraPos - a->getWorldPosition());
            float db = glm::length(cameraPos - b->getWorldPosition());
            return da > db; // farthest first
        });

    for (SceneNode* n : transparentNodes)
    {
        n->draw(shader);
    }

    // restore depth write
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void Renderer::clear()
{
    opaqueNodes.clear();
    transparentNodes.clear();
}
