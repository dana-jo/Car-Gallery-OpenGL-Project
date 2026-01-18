#include "Model.h"
#include "MeshNode.h"

#include "../utils/Mesh.h"
#include "../graphics/Material.h"
#include "../graphics/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h> // <-- Add this include at the top

#include <iostream>
#include <algorithm>
#include <cfloat>



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
        //aiProcess_FlipUVs |
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

    // ---- Load material UV transform (GLTF fix) ----
    glm::vec2 uvScale(1.0f, 1.0f);
    glm::vec2 uvOffset(0.0f, 0.0f);

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        aiUVTransform transform;
        // Try both BASE_COLOR and DIFFUSE for maximum compatibility
        if (mat->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_BASE_COLOR, 0), transform) == AI_SUCCESS ||
            mat->Get(AI_MATKEY_UVTRANSFORM(aiTextureType_DIFFUSE, 0), transform) == AI_SUCCESS)
        {
            uvScale.x = transform.mScaling.x;
            uvScale.y = transform.mScaling.y;
            uvOffset.x = transform.mTranslation.x;
            uvOffset.y = transform.mTranslation.y;
        }
    
    }

    // ---- Vertices ----
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex v{};

        v.position[0] = mesh->mVertices[i].x;
        v.position[1] = mesh->mVertices[i].y;
        v.position[2] = mesh->mVertices[i].z;

        if (mesh->HasNormals())
        {
            v.normal[0] = mesh->mNormals[i].x;
            v.normal[1] = mesh->mNormals[i].y;
            v.normal[2] = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 uv(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );

            // 🔥 THIS IS THE FIX 🔥
            uv = uv * uvScale + uvOffset;

            v.texCoords[0] = uv.x;
            v.texCoords[1] = uv.y;
        }

        vertices.push_back(v);
    }

    // ---- Indices ----
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    Mesh* engineMesh = new Mesh(vertices, indices);
    engineMesh->setup();

    // ---- Material ----
    Material* material = new Material();

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

        aiString texturePath;
        if (aiMat->GetTexture(aiTextureType_BASE_COLOR, 0, &texturePath) == AI_SUCCESS ||
            aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
        {
            std::string texPath = texturePath.C_Str();
            std::replace(texPath.begin(), texPath.end(), '\\', '/');

            material->diffuse = new Texture(directory + "/" + texPath);
            material->hasTexture = true;
            material->updateFromTexture();
        }
    }

    return new MeshNode(engineMesh, material);
}

