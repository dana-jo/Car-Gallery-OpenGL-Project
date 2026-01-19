#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Shader.h"
#include "core/LightNode.h"
#include "Renderer.h"
#include "scene/World.h"
#include "scene/MainCar.h"
#include "scene/GalleryShell.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "Camera.h"
#include "objects/WallWithHole.h"

#include "objects/Box.h"
#include "graphics/Skybox.h"
#include "objects/Polygon.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Model.h>
#include <FamilyCar.h>
#include "../ZZZ.h"


// ------------------------------------------------------------
// Simple camera values
// ------------------------------------------------------------

glm::mat4 getProjection(int w, int h)
{
    return glm::perspective(
        glm::radians(60.0f),
        (float)w / (float)h,
        0.1f,
        500.0f
    );
}

// ------------------------------------------------------------

int main()
{
    // --------------------------------------------------------
    // GLFW / OpenGL init
    // --------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Transparency Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    Camera camera(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

   
    Shader shader("shaders/light_shader.vert", "shaders/light_shader.frag");

    Renderer renderer;
    renderer.shader = shader;

    Texture blueTex("assets/textures/Purple.png");
	Texture brickTex("assets/textures/window1.png");

    Material blueMat(&blueTex, { 1.0f, 1.0f });
	Material brickMaterial(&brickTex, { 1.0f, 1.0f });
   
    // --------------------------------------------------------
    // Objects
    // --------------------------------------------------------
    /*Model model("assets/pine/scrubPine.obj");
    model.position = { 0.0f, -1.0f, -3.0f };
    model.scale = { 0.005f, 0.005f, 0.005f };*/

    Skybox skybox({
    "assets/skybox/right.jpg",
    "assets/skybox/left.jpg",
    "assets/skybox/top.jpg",
    "assets/skybox/bottom.jpg",
    "assets/skybox/front.jpg",
    "assets/skybox/back.jpg"
        });

	World* world = new World();

    bool cPressedLastFrame = false;



    float lastTime = (float)glfwGetTime();

    

    while (!glfwWindowShouldClose(window))
    {
        world->gallery->shell->r4->car->setCamera(&camera, window);

        glfwPollEvents();

        camera.update();

        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getView();
        glm::mat4 projection = getProjection(1280, 720);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

		shader.setVec3("viewPos", camera.getPosition());

		shader.setFloat("material_shininess", 32.0f);

        shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.1f));
        shader.setVec3("dirLight.ambient", glm::vec3(0.25f));
        shader.setVec3("dirLight.diffuse", glm::vec3(0.12f));
        shader.setVec3("dirLight.specular", glm::vec3(0.03f));
        shader.setBool("dirLight.enabled", true);

        renderer.setSceneRoot(world);
        renderer.submit(world);
		//renderer.submit(&model);
        world->update(dt, camera.getPosition());

        renderer.drawAll(camera.getPosition());
        renderer.clear();

        skybox.draw(view, projection);

        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}