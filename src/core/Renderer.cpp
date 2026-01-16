#include "Renderer.h"
#include "SceneNode.h"
#include <algorithm>
#include <glad/glad.h>
#include "../core/Shader.h"
#include "core/LightNode.h"

void collectLights(SceneNode* node, std::vector<LightNode*>& out)
{
    if (!node) return;

    if (auto* light = dynamic_cast<LightNode*>(node))
    {
        out.push_back(light);
    }

    for (auto* c : node->children)
        collectLights(c, out);
}

void Renderer::uploadLights(SceneNode* root, const glm::vec3& cameraPos)
{
    std::vector<LightNode*> lights;
    collectLights(root, lights);

    int pointCount = 0;
    int spotCount = 0;

    for (auto* l : lights)
    {
        if (l->type == LightType::Point && pointCount < 15)
        {
            std::string base = "pointLights[" + std::to_string(pointCount) + "]";
            shader.setVec3(base + ".position", l->getWorldPosition());
            shader.setVec3(base + ".ambient", l->ambient);
            shader.setVec3(base + ".diffuse", l->diffuse);
            shader.setVec3(base + ".specular", l->specular);
            shader.setFloat(base + ".constant", l->constant);
            shader.setFloat(base + ".linear", l->linear);
            shader.setFloat(base + ".quadratic", l->quadratic);
            shader.setBool(base + ".enabled", true);
            pointCount++;
        }

        if (l->type == LightType::Spot && spotCount < 15)
        {
            std::string base = "spotLights[" + std::to_string(spotCount) + "]";
            shader.setVec3(base + ".position", l->getWorldPosition());
            shader.setVec3(base + ".direction", l->direction);
            shader.setFloat(base + ".cutOff", l->cutOff);
            shader.setFloat(base + ".outerCutOff", l->outerCutOff);
            shader.setVec3(base + ".ambient", l->ambient);
            shader.setVec3(base + ".diffuse", l->diffuse);
            shader.setVec3(base + ".specular", l->specular);
            shader.setFloat(base + ".constant", l->constant);
            shader.setFloat(base + ".linear", l->linear);
            shader.setFloat(base + ".quadratic", l->quadratic);
            shader.setBool(base + ".enabled", true);
            spotCount++;
        }
    }

    shader.setInt("numPointLights", pointCount);
    shader.setInt("numSpotLights", spotCount);
}

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

    if (sceneRoot)
        uploadLights(sceneRoot, cameraPos);

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
