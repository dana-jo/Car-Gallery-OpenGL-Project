#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../utils/Mesh.h"
#include "../graphics/Texture.h"
#include "../core/Shader.h"
#include "../core/SceneNode.h"

class Object : public SceneNode
{
protected:
    Mesh* mesh = nullptr;

public:
    Object();
    virtual ~Object() = default;

    virtual void draw(Shader& shader) override;

};
