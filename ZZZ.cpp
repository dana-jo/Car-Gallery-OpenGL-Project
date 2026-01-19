#include "ZZZ.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"
#include "../objects/Polygon.h"
#include "../graphics/Material.h"
#include <glm/gtc/matrix_transform.hpp>
#include "carDoor.h"
#include <LightNode.h>
#include "../core/SceneNode.h"
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

// BOX
// Box* box = new Box(width, height, depth);
// box->position = { x, y, z };
// box->rotation.y = glm::radians(45.0f);
// addChild(box);
// 
// box->setFaceMaterial(BoxFace::Front, matFront);
// box->setFaceMaterial(BoxFace::Top, matRoof);
// 
// box->setMaterial(mat);

// Cylinder
// Cylinder* wheel = new Cylinder(radius, width, segments);
// wheel->position = { x, y, z };
// wheel->rotation.z = glm::radians(90.0f); // wheels lie sideways
// addChild(wheel);
// 
// wheel->setPartMaterial(CylinderPart::Side, tireMat);
// wheel->setPartMaterial(CylinderPart::Top, rimMat);
// wheel->setPartMaterial(CylinderPart::Bottom, rimMat);

// Polygon
// std::vector<glm::vec2> shape = {
//     {-1.0f, 0.0f},
//     { 1.0f, 0.0f},
//     { 0.8f, 0.6f},
//     {-0.8f, 0.6f}
// };
// 
// Polygon* glass = new Polygon(shape, 0.1f);
// glass->position = { 0, 1.2f, 1.5f };
// glass->setMaterial(glassMat);
// addChild(glass);

ZZZ::ZZZ()
{
    float scale = 1.0f;
    float width = 4 * scale; // z length

    float eyesRadius = 0.45 * scale;
    float eyesExtra = 0.1 * scale;
    float smallEyesRadius = eyesRadius * 0.2f;
    float bodyExtra = 0.05 * scale;

    // y lengths
    float frontHeight = (eyesRadius * 2) + 0.1f;
    float bottomY = -frontHeight / 2.0f;
    float height = 3.3 * scale;

    // x lengths
    float frontLength = width - 2;
    float middleLength = width - 1;
    float backLength = (width - 1) * scale;

    // x positions (objects touch end-to-end)
    float frontX = -0.5f;
    float middleX = frontX - frontLength / 2.0f - middleLength / 2.0f;
    float backX = middleX - middleLength / 2.0f - backLength / 2.0f;


    Material* transparentMat = new Material(new Texture("assets/ZZZ/transparent.png"));
    Material* greenMat = new Material(new Texture("assets/ZZZ/green.png"));
    Material* blackMat = new Material(new Texture("assets/ZZZ/black.png"));
    Material* orangeMat = new Material(new Texture("assets/ZZZ/orange.png"));
    Material* frontLights = new Material(new Texture("assets/ZZZ/frontLights.png"));
    Material* underVintage = new Material(new Texture("assets/ZZZ/underVintage.png"));
    Material* eyesSide = new Material(new Texture("assets/ZZZ/eyes.png"));
    Material* bodySide = new Material(new Texture("assets/ZZZ/body.png"));
    Material* bodyFront = new Material(new Texture("assets/ZZZ/front.png"));
    Material* backSide1 = new Material(new Texture("assets/ZZZ/backSide_front.png"));
    Material* backSide2 = new Material(new Texture("assets/ZZZ/backSide_back.png"));
    Material* backTop = new Material(new Texture("assets/ZZZ/back_top.png"));
    Material* backBack = new Material(new Texture("assets/ZZZ/back_back.png"));
    Material* backR = new Material(new Texture("assets/ZZZ/back_rotate.png"));
    Material* middleFront = new Material(new Texture("assets/ZZZ/middle_front.png"));
    Material* door1 = new Material(new Texture("assets/ZZZ/door1.png"));
    Material* door2 = new Material(new Texture("assets/ZZZ/door2.png"));
    Material* steeringWheelMat = new Material(new Texture("assets/ZZZ/steeringWheel.png"));
    Material* leather = new Material(new Texture("assets/ZZZ/leather.jpg"));
    Material* wheelMat = new Material(new Texture("assets/ZZZ/wheel.jpg"));
    Material* wheelSideMat = new Material(new Texture("assets/ZZZ/wheel_side.jpg"));

    float totalBodyLength = frontLength + middleLength + backLength;
    float bodyStartX = frontX + frontLength / 2.0f;
    float bodyCenterX = bodyStartX - totalBodyLength / 2.0f;

    Box* under = new Box(
        frontLength + middleLength + backLength + 2 * bodyExtra ,
        bodyExtra + 0.1f,
        width + 2 * bodyExtra
    );
    under->position = {
    bodyCenterX,
    bottomY - (bodyExtra + 0.1f) / 2,
    0
    };
    under->setMaterial(underVintage);
    under->setFaceMaterial(BoxFace::Top, transparentMat);
    addChild(under);

    // the front
    Box* frontBody = new Box(frontLength, frontHeight, width);
    frontBody->position = { frontX, bottomY + frontHeight / 2, 0 };

    frontBody->setMaterial(bodySide);
    frontBody->setFaceMaterial(BoxFace::Top, blackMat);
    frontBody->setFaceMaterial(BoxFace::Right, bodyFront);
    frontBody->setFaceMaterial(BoxFace::Left, greenMat);
    addChild(frontBody);

    float eyeX = eyesExtra / 2 + 0.01f - 0.5f;
    float eyeZ = width / 2 - eyesRadius + 0.02f;

    Cylinder* eyes1 = new Cylinder(eyesRadius, frontLength + eyesExtra, 20);
    eyes1->position = { eyeX, eyesRadius,  eyeZ };
    eyes1->rotation.z = glm::radians(90.0f);
    eyes1->setPartMaterial(CylinderPart::Side, eyesSide);
    eyes1->setPartMaterial(CylinderPart::Top, greenMat);
    eyes1->setPartMaterial(CylinderPart::Bottom, frontLights);
    addChild(eyes1);

    Cylinder* eyes2 = new Cylinder(eyesRadius, frontLength + eyesExtra, 20);
    eyes2->position = { eyeX, eyesRadius, -eyeZ };
    eyes2->rotation.z = glm::radians(90.0f);
    eyes2->setPartMaterial(CylinderPart::Side, eyesSide);
    eyes2->setPartMaterial(CylinderPart::Top, greenMat);
    eyes2->setPartMaterial(CylinderPart::Bottom, frontLights);
    addChild(eyes2);

    float smallEyeX = eyeX;
    float smallEyeY = 0;
    float smallEyeZ = width / 4;

    Cylinder* smallEye1 = new Cylinder(
        smallEyesRadius,
        frontLength + eyesExtra,
        20
    );

    smallEye1->position = {
        smallEyeX,
        smallEyeY,
        smallEyeZ
    };
    smallEye1->rotation.z = glm::radians(90.0f);
    smallEye1->setPartMaterial(CylinderPart::Side, eyesSide);
    smallEye1->setPartMaterial(CylinderPart::Top, greenMat);
    smallEye1->setPartMaterial(CylinderPart::Bottom, orangeMat);
    addChild(smallEye1);

    Cylinder* smallEye2 = new Cylinder(
        smallEyesRadius,
        frontLength + eyesExtra,
        20
    );
    smallEye2->position = {
        smallEyeX,
        smallEyeY,
        -smallEyeZ
    };
    smallEye2->rotation.z = glm::radians(90.0f);
    smallEye2->setPartMaterial(CylinderPart::Side, eyesSide);
    smallEye2->setPartMaterial(CylinderPart::Top, greenMat);
    smallEye2->setPartMaterial(CylinderPart::Bottom, orangeMat);
    addChild(smallEye2);

    // the middle
    Box* middleBody = new Box(middleLength, height, width);
    middleBody->position = {
        middleX,
        bottomY + height / 2,
        0
    };

    middleBody->setMaterial(greenMat);
    middleBody->setFaceMaterial(BoxFace::Right, middleFront);
    middleBody->setFaceMaterial(BoxFace::Left, transparentMat);
    middleBody->setFaceMaterial(BoxFace::Front, transparentMat);
    middleBody->setFaceMaterial(BoxFace::Back, door2);
    addChild(middleBody);

    // the back
    Box* backBody = new Box(backLength, height, width);
    backBody->position = {
        backX,
        bottomY + height / 2,
        0
    };
    backBody->setMaterial(greenMat);
    backBody->setFaceMaterial(BoxFace::Right, transparentMat);
    backBody->setFaceMaterial(BoxFace::Front, backSide1);
    backBody->setFaceMaterial(BoxFace::Back, backSide2);
    backBody->setFaceMaterial(BoxFace::Top, backTop);
    backBody->setFaceMaterial(BoxFace::Left, backBack);
    addChild(backBody);

     Box* backWindow = new Box(0.2, height - 0.5 , width);
     backWindow->position = { backX - 1.25, height / 2 + 0.19 , 0 };
     backWindow->rotation.z = glm::radians(-42.0f);
     backWindow->setMaterial(transparentMat);
     backWindow->setFaceMaterial(BoxFace::Right, backR);
     addChild(backWindow);

     // the door
     door = new CarDoor(
         middleLength,
         height,
         0.01f
     );

     door->position = {
         middleX + middleLength / 2.0f - 0.01f,
         bottomY + height / 2,
         width / 2 + 0.01f
     };
     door->rotation.y = glm::radians(180.0f);

     door->setDoorMaterial(door1);
     addChild(door);

     // tableau
      float tableauLength = 0.5;
      float tableauHeight = frontHeight + 0.5;
      float tableauX = frontX - frontLength / 2 - tableauLength / 2 - 0.001;
      float tableauY = bottomY + tableauHeight / 2;
      Box* tableau = new Box(tableauLength, tableauHeight, width - 0.2);
      tableau->position = {
          tableauX,
          tableauY,
          0
      };
      tableau->setMaterial(leather);
      addChild(tableau);

      // the steering wheel
      SceneNode* steeringPivot = new SceneNode();
      steeringPivot->position = {
          tableauX - tableauLength / 2 - 0.1f,
          tableauY + tableauHeight / 2 + 0.1f,
          width / 4 + 0.1f
      };
      steeringPivot->rotation.z = glm::radians(45.0f);
      addChild(steeringPivot);

      steeringWheel = new Cylinder(0.4f, 0.05f, 20);
      steeringWheel->setMaterial(steeringWheelMat);
      steeringWheel->setPartMaterial(CylinderPart::Side, blackMat);
      steeringWheel->position = { 0, 0, 0 };
      steeringPivot->addChild(steeringWheel);

      // the lights
      lights[0] = new LightNode(LightType::Point);
      lights[0]->ambient = glm::vec3(0.0f);
      lights[0]->diffuse = glm::vec3(0.0f);
      lights[0]->specular = glm::vec3(0.0f);
      lights[0]->position = { eyeX + frontLength, eyesRadius, eyeZ };
      addChild(lights[0]);

      lights[1] = new LightNode(LightType::Point);
      lights[1]->ambient = glm::vec3(0.0f);
      lights[1]->diffuse = glm::vec3(0.0f);
      lights[1]->specular = glm::vec3(0.0f);
      lights[1]->position = { eyeX + frontLength, eyesRadius, -eyeZ };
      addChild(lights[1]);

      isLightsOn = false;

      //glm::vec3 forward = glm::normalize(glm::vec3(-1, 0, 0));
      //SceneNode* s = new SceneNode();
      //s -> position = { eyeX + frontLength, eyesRadius,  eyeZ };
      //s->rotation.x = 90;
      //addChild(s);

      //lights[0] = new LightNode(LightType::Spot);
      //lights[0]->position = { 0, 0,  0 };
      //lights[0]->direction = forward;
      //lights[0]->ambient = glm::vec3(0.05f);
      //lights[0]->diffuse = glm::vec3(2.5f);
      //lights[0]->specular = glm::vec3(1.0f);
      //lights[0]->cutOff = glm::cos(glm::radians(20.5f));
      //lights[0]->outerCutOff = glm::cos(glm::radians(10.0f));
      //lights[0]->constant = 1.0f;
      //lights[0]->linear = 0.02f;
      //lights[0]->quadratic = 0.001f;
      //s->addChild(lights[0]);

      //lights[1] = new LightNode(LightType::Spot);
      //lights[1]->position = { eyeX + frontLength, eyesRadius, -eyeZ };
      //lights[1]->direction = forward;
      //lights[1]->ambient = glm::vec3(0.05f);
      //lights[1]->diffuse = glm::vec3(2.5f);
      //lights[1]->specular = glm::vec3(1.0f);
      //lights[1]->cutOff = glm::cos(glm::radians(12.5f));
      //lights[1]->outerCutOff = glm::cos(glm::radians(20.0f));
      //lights[1]->constant = 1.0f;
      //lights[1]->linear = 0.02f;
      //lights[1]->quadratic = 0.001f;
      //addChild(lights[1]);



      // the seats
      float seatWidth = width / 2 - 0.5;
      float seatHeight = 0.4;

      float seatBGap = 0.7;
      float seatBLength = middleLength - tableauLength - seatBGap;
      seatXMax = frontX - frontLength / 2 - tableauLength - seatBLength / 2 - seatBGap;
      float seatY = bottomY + seatHeight / 2 + 0.3;
      float seatZ = width / 4;

      float seatTlength = 1.5;
      float seatTX = -seatBLength / 2 + seatHeight / 2;
      float seatTY = seatHeight / 2 + seatTlength / 2;

      seats[0] = new SceneNode();
      seats[0]-> position = {
          seatXMax,
          seatY,
          seatZ
      };
      addChild(seats[0]);
      Box* seatBottom = new Box(seatBLength, seatHeight, seatWidth);
      seatBottom->position = {0, 0, 0};
      seatBottom->setMaterial(leather);
      seats[0]->addChild(seatBottom);
      Box* seatTop = new Box(seatHeight, seatTlength, seatWidth);
      seatTop->position = { seatTX, seatTY, 0 };
      seatTop->setMaterial(leather);
      seats[0]->addChild(seatTop);

      seats[1] = new SceneNode();
      seats[1]->position = {
          seatXMax,
          seatY,
          - seatZ
      };
      addChild(seats[1]);
      Box* seatBottom1 = new Box(seatBLength, seatHeight, seatWidth);
      seatBottom1->position = { 0, 0, 0 };
      seatBottom1->setMaterial(leather);
      seats[1]->addChild(seatBottom1);
      Box* seatTop1 = new Box(seatHeight, seatTlength, seatWidth);
      seatTop1->position = { seatTX, seatTY, 0 };
      seatTop1->setMaterial(leather);
      seats[1]->addChild(seatTop1);


      // wheels 
      float wheelRadius = 0.7f;
      float wheelWidth = 0.4f;
      float wheelY = bottomY;
      float frontWheelX = frontX + frontLength / 2.0f - 1;
      float backWheelX = backX - backLength / 2.0f + 1.2f;
      float wheelZ = width / 2;

      // Front left
      wheels[0] = new Cylinder(wheelRadius, wheelWidth, 24);
      wheels[0]->position = { frontWheelX, wheelY,  wheelZ };
      wheels[0]->rotation.x = glm::radians(90.0f);
      wheels[0]->setMaterial(wheelMat);
      wheels[0]->setPartMaterial( CylinderPart::Side ,wheelSideMat);
      addChild(wheels[0]);

      // Front right
      wheels[1] = new Cylinder(wheelRadius, wheelWidth, 24);
      wheels[1]->position = { frontWheelX, wheelY, -wheelZ };
      wheels[1]->rotation.x = glm::radians(90.0f);
      wheels[1]->setMaterial(wheelMat);
      wheels[1]->setPartMaterial(CylinderPart::Side, wheelSideMat);
      addChild(wheels[1]);

      // Back left
      wheels[2] = new Cylinder(wheelRadius, wheelWidth, 24);
      wheels[2]->position = { backWheelX, wheelY,  wheelZ };
      wheels[2]->rotation.x = glm::radians(90.0f);
      wheels[2]->setMaterial(wheelMat);
      wheels[2]->setPartMaterial(CylinderPart::Side, wheelSideMat);
      addChild(wheels[2]);

      // Back right
      wheels[3] = new Cylinder(wheelRadius, wheelWidth, 24);
      wheels[3]->position = { backWheelX, wheelY, -wheelZ };
      wheels[3]->rotation.x = glm::radians(90.0f);
      wheels[3]->setMaterial(wheelMat);
      wheels[3]->setPartMaterial(CylinderPart::Side, wheelSideMat);
      addChild(wheels[3]);
}

void ZZZ::rotateSteering(float amount)
{
    steeringWheel->rotation.y += amount;
}

void ZZZ:: toggleLights() {

    if (isLightsOn) {
        lights[0]->ambient = glm::vec3(0.0f);
        lights[0]->diffuse = glm::vec3(0.0f);
        lights[0]->specular = glm::vec3(0.0f);

        lights[1]->ambient = glm::vec3(0.0f);
        lights[1]->diffuse = glm::vec3(0.0f);
        lights[1]->specular = glm::vec3(0.0f);

        isLightsOn = false;
    }
    else {
        lights[0]->ambient = glm::vec3(0.3f);
        lights[0]->diffuse = glm::vec3(0.5f);
        lights[0]->specular = glm::vec3(1.0f);

        lights[1]->ambient = glm::vec3(0.3f);
        lights[1]->diffuse = glm::vec3(0.5f);
        lights[1]->specular = glm::vec3(1.0f);

        isLightsOn = true;
    }

}

bool ZZZ::moveSeats(float amount)
{
    float before = seats[0]->position.x;

    seats[0]->position.x += amount;
    seats[0]->position.x = glm::clamp(
        seats[0]->position.x,
        seatXMax - 1.5f,
        seatXMax
    );

    return seats[0]->position.x != before;
}

void ZZZ::rotateWheels(float amount) {
    for (int i = 0; i < 4; ++i)
        wheels[i]->rotation.y += amount;
}


void ZZZ::update(float dt, const glm::vec3& cameraPos) {
    if (!window) return;

    door->update(dt, cameraPos);

    glm::vec3 wallWorldPos = getWorldPosition();
    float dist = glm::distance(wallWorldPos, cameraPos);

    // getting inside the car
    bool cPressedNow = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    if (cPressedNow && !cPressedLastFrame)
    {

        if (dist <= 30.0f)
        {
            glm::vec3 seatPos = wallWorldPos ;

            float seatYaw = 0.0f;
            float seatPitch = 0.0f;

            camera->toggleInsideCar(seatPos, seatYaw, seatPitch);
        }
    }
    cPressedLastFrame = cPressedNow;

    // close to the car => turning on and off the lights
    if (dist <= 30.0f) {
        bool lPressedNow = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
        // the lights
        if (lPressedNow && !lPressedLastFrame) {
            toggleLights();
        }
        lPressedLastFrame = lPressedNow;

        // the wheels
        float z = 0.2;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            rotateWheels(-z);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            rotateWheels(z);
        }
    }

    // inside the car => moving the steering wheeel / seat
    if (camera->isInsideCar())
    {
        // the steering wheel
        float w = 0.05;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            rotateSteering(w);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            rotateSteering(-w);
        }
        // th seats
        float s = 0.05;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            if (moveSeats(s))
                camera->position.x += s;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            if (moveSeats(-s))
                camera->position.x -= s;
        }
    }
}