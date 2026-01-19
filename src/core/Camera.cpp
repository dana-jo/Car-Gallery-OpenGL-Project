#include "Camera.h"
#include "Collision.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GLFWwindow* win)
    : window(win)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

// ---------------- Update called each frame ----------------
void Camera::update(const std::vector<SceneNode*>& worldObjects)
{
    static float lastTime = (float)glfwGetTime();
    float current = (float)glfwGetTime();
    float dt = current - lastTime;
    lastTime = current;

    updateKeyboard(dt, worldObjects);
    updateMouse();
}

// ---------------- Check if a position is free ----------------
bool Camera::canMove(const glm::vec3& newPos, const std::vector<SceneNode*>& worldObjects)
{
    SceneNode camNode;
    camNode.position = newPos;
    camNode.collider = collider;

    for (SceneNode* obj : worldObjects)
    {
        if (checkCollisionRecursive(&camNode, obj))
            return false;
    }

    return true;
}

// ---------------- Keyboard input with per-axis collision ----------------
void Camera::updateKeyboard(float dt, const std::vector<SceneNode*>& worldObjects)
{
    // no WASD movement inside car
    if(insideCar)
        return;

    // normal  movement
    glm::vec3 delta(0.0f);
    float velocity = speed * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) delta += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) delta -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) delta -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) delta += right * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) delta += up * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) delta -= up * velocity;

    // Move X separately
    glm::vec3 testPosX = position + glm::vec3(delta.x, 0, 0);
    if (canMove(testPosX, worldObjects)) position.x = testPosX.x;

    // Move Y separately
    glm::vec3 testPosY = position + glm::vec3(0, delta.y, 0);
    if (canMove(testPosY, worldObjects)) position.y = testPosY.y;

    // Move Z separately
    glm::vec3 testPosZ = position + glm::vec3(0, 0, delta.z);
    if (canMove(testPosZ, worldObjects)) position.z = testPosZ.z;
}

// ---------------- Mouse look ----------------
void Camera::updateMouse()
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
    {
        firstMouse = true;
        return;
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = glm::clamp(pitch, -85.0f, 85.0f);

    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, up));
}

// ---------------- View matrix ----------------
glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

// inside the car stuff
void Camera::toggleInsideCar(const glm::vec3& seatPos, float seatYaw, float seatPitch)
{
    if (!insideCar)
    {
        // save last position
        savedPosition = position;
        savedYaw = yaw;
        savedPitch = pitch;

        // move camera inside car
        position = seatPos;
        yaw = seatYaw;
        pitch = seatPitch;

        insideCar = true;
    }
    else
    {
        // restore state
        position = savedPosition;
        yaw = savedYaw;
        pitch = savedPitch;

        insideCar = false;
    }

    // recompute direction vectors
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, up));
}
