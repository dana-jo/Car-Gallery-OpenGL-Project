#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(GLFWwindow* window);

    void update();
    glm::vec3 getPosition() const;
    glm::mat4 getView() const;

    glm::vec3 position{ 0.0f, 0.0f, 3.0f };

    // inside the car stuff
    void toggleInsideCar(const glm::vec3& seatPos, float seatYaw, float seatPitch);
    bool isInsideCar() const { return insideCar; }


private:
    GLFWwindow* window;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float speed = 15.0f;
    float sensitivity = 0.1f;

    glm::vec3 front{ 0.0f, 0.0f, -1.0f };
    glm::vec3 up{ 0.0f, 1.0f, 0.0f };
    glm::vec3 right{ 1.0f, 0.0f, 0.0f };


    bool firstMouse = true;
    float lastX = 640.0f;
    float lastY = 360.0f;

    void updateMouse();
    void updateKeyboard(float dt);

    // inside the car stuff 
    bool insideCar = false;
    glm::vec3 savedPosition;
    float savedYaw;
    float savedPitch;
};
