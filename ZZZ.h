#pragma once
#include "carDoor.h"
#include "../core/SceneNode.h"
class Camera;
struct GLFWwindow;

class Material;
class Box;
class Cylinder;
class Polygon;
class LightNode;

class ZZZ : public SceneNode
{
public:
    ZZZ();

    void setCamera(Camera* cam, GLFWwindow* win) { camera = cam; window = win; }
    void update(float dt, const glm::vec3& cameraPos) override;

private:
    Cylinder* steeringWheel = nullptr;
    LightNode* lights[2] = { nullptr, nullptr};
    SceneNode* seats[2] = { nullptr, nullptr };
    Cylinder* wheels[4] = { nullptr, nullptr, nullptr, nullptr };
    CarDoor* door = nullptr;

    Camera* camera = nullptr;
    GLFWwindow* window = nullptr;
    bool cPressedLastFrame = false;
    bool lPressedLastFrame = false;

    float seatXMax;
    float seatXMin;

    bool isLightsOn;

    void rotateSteering(float amount);
    void toggleLights();
    bool moveSeats(float amount);
    void rotateWheels(float amount);
};