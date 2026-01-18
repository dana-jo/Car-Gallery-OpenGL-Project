#include "Model.h"
#include "MeshNode.h"

#include "../utils/Mesh.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>


Model::Model(const std::string& path)
{
    loadModel(path);
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene || !scene->mRootNode)
    {
        std::cerr << "[ASSIMP ERROR] "
            << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of("/\\"));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshNode* meshNode = processMesh(mesh, scene);
        addChild(meshNode);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

MeshNode* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 min(FLT_MAX);
    glm::vec3 max(-FLT_MAX);


    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex v;

        v.position[0] = mesh->mVertices[i].x;
        v.position[1] = mesh->mVertices[i].y;
        v.position[2] = mesh->mVertices[i].z;

        min = glm::min(min, glm::vec3(v.position[0], v.position[1], v.position[2]));
        max = glm::max(max, glm::vec3(v.position[0], v.position[1], v.position[2]));

        if (mesh->HasNormals())
        {
            v.normal[0] = mesh->mNormals[i].x;
            v.normal[1] = mesh->mNormals[i].y;
            v.normal[2] = mesh->mNormals[i].z;
        }
        else
        {
            v.normal[0] = 0.0f;
            v.normal[1] = 0.0f;
            v.normal[2] = 0.0f;
        }

        if (mesh->mTextureCoords[0])
        {
            v.texCoords[0] = mesh->mTextureCoords[0][i].x;
            v.texCoords[1] = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            v.texCoords[0] = 0.0f;
            v.texCoords[1] = 0.0f;
        }

        vertices.push_back(v);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh* engineMesh = new Mesh(vertices, indices);
    engineMesh->setup();

    Material* material = nullptr;

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

        aiString texturePath;
        if (aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
        {
            std::string fullPath = directory + "/" + texturePath.C_Str();
            Texture* texture = new Texture(fullPath);
            material = new Material(texture);
        }
    }
    glm::vec3 size = max - min;
    glm::vec3 center = (max + min) * 0.5f;

    return new MeshNode(engineMesh, material , size, center);
}
