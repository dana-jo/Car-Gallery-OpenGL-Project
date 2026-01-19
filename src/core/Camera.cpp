#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(GLFWwindow* win)
    : window(win)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // Hide and capture the cursor GLFW_CURSOR_DISABLED
}

void Camera::update()
{
    static float lastTime = glfwGetTime();
    float current = glfwGetTime();
    float dt = current - lastTime;
    lastTime = current;

    updateKeyboard(dt);
    updateMouse();
}

void Camera::updateKeyboard(float dt)
{
    // no WASD movement inside car
    if(insideCar)
        return;

    // normal  movement
    float velocity = speed * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += velocity * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= velocity * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= velocity * right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += velocity * right;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		position += velocity * up;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position -= velocity * up;
    //position.x = glm::clamp(position.x, -2.5f, 2.5f);
    //position.y = glm::clamp(position.y, -5.5f, 5.5f);
    //position.z = glm::clamp(position.z, 0.f, 1.5f);

}

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
