#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../core/Shader.h"
#include "../core/Renderer.h"
#include "../objects/Box.h"
#include "../objects/Cylinder.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void framebuffer_size_callback(GLFWwindow*, int w, int h)
{
    glViewport(0, 0, w, h);
}

int main()
{
    // ---------- GLFW ----------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Box Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    // ---------- Shader ----------
    Shader shader("shaders/basic_shader.vert", "shaders/basic_shader.frag");


    Texture* front = new Texture("assets/textures/Red.png");
    Texture* back = new Texture("assets/textures/Green.png");
    Texture* left = new Texture("assets/textures/Blue.png");
    Texture* right = new Texture("assets/textures/White.png");
    Texture* top = new Texture("assets/textures/Yellow.png");
    Texture* bottom = new Texture("assets/textures/Purple.png");


    // ---------- Camera matrices ----------
    glm::mat4 view = glm::translate(glm::mat4(1.0f), { 0, 0, -8 });
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    // Root car body
    Box* car = new Box(4.0f, 1.2f, 2.0f);
    car->position = { 0, 0, 0 };
	car->setTexture(front);

    // Door (child of car)
    Box* door = new Box(1.2f, 1.0f, 0.1f);
    door->position = { 1.6f, 0.0f, 1.05f }; // relative to car
    car->addChild(door);
	door->setTexture(left);

    // Wheel FL
    Cylinder* wheelFL = new Cylinder(0.4f, 0.3f, 32);
    wheelFL->rotation.x = glm::radians(90.0f);
    wheelFL->position = { -1.4f, -0.6f, 1.0f };
    car->addChild(wheelFL);
	wheelFL->setTexture(right);

    // Wheel FR
    Cylinder* wheelFR = new Cylinder(0.4f, 0.3f, 32);
    wheelFR->rotation.x = glm::radians(90.0f);
    wheelFR->position = { 1.4f, -0.6f, 1.0f };
    car->addChild(wheelFR);
	wheelFR->setTexture(top);



    // ---------- Render loop ----------
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        
        shader.setInt("texture1", 0);
        shader.setMat4("view", view);

        shader.setMat4("projection", projection);

		car->draw(shader);
        car->position.x += 0.001f;

        door->rotation.y = glm::radians(45.0f);

        wheelFL->rotation.z += 0.02f;
        wheelFR->rotation.z += 0.02f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

