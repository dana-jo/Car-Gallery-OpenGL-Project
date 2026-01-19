#pragma once
#include "../core/SceneNode.h"
#include <string>

class Model : public SceneNode
{
public:
    Model(const std::string& path);
    void enableBoxCollider();


private:
    void loadModel(const std::string& path);
    void processNode(struct aiNode* node, const struct aiScene* scene);
    class MeshNode* processMesh(struct aiMesh* mesh, const struct aiScene* scene);

    std::string directory;
};