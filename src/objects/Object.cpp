#include "../objects/Object.h"
#include "../core/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

Object::Object() {}

void Object::draw(Shader& shader)
{
    shader.setMat4("model", getWorldMatrix());
    
    if (mesh)
        mesh->draw();

    SceneNode::draw(shader); // draw children
}





