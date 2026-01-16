#pragma once
#include <vector>
#include <glm/glm.hpp>

//class SceneNode;
//class Shader;
#include "SceneNode.h"
#include "Shader.h"

class Renderer
{
public:
    Shader shader;

    std::vector<SceneNode*> opaqueNodes;
    std::vector<SceneNode*> transparentNodes;

    Renderer() = default;

    // Submit nodes (call this for every visible root/object each frame)
    void submit(SceneNode* node);

    // Draw all submitted nodes. Pass camera world position (for sorting)
    void drawAll(const glm::vec3& cameraPos);

    // Clear lists (call at end or start of frame)
    void clear();
    void setSceneRoot(SceneNode* root) { sceneRoot = root; }

    void uploadLights(SceneNode* root, const glm::vec3& cameraPos);

private:
    SceneNode* sceneRoot = nullptr;
};
