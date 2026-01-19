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
#include <assimp/version.h>
#include <FamilyCar.h>
#include "AudioSystem.h"
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
    AudioSystem::init();

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

    

    Skybox skybox({
        "assets/skybox/right.jpg",
        "assets/skybox/left.jpg",
        "assets/skybox/top.jpg",
        "assets/skybox/bottom.jpg",
        "assets/skybox/front.jpg",
        "assets/skybox/back.jpg"
    });

    Skybox nightSkybox({
        "assets/night_skybox/right.jpg",
        "assets/night_skybox/left.jpg",
        "assets/night_skybox/top.jpg",
        "assets/night_skybox/bottom.jpg",
        "assets/night_skybox/front.jpg",
        "assets/night_skybox/back.jpg"
        });
    bool isNight = false;
    bool keyPressed = false;

	World* world = new World();

    bool cPressedLastFrame = false;



    //AudioSystem::playSound("assets/audios/oiia-oiia-spinning-cat.wav"); to test it if u want

    float lastTime = (float)glfwGetTime();

    // after creating camera
        camera.collider = new BoxCollider({ 0.5f, 1.8f, 0.5f });

    // collect world objects with colliders
    std::vector<SceneNode*> worldObjects;

    


    while (!glfwWindowShouldClose(window))
    {
        world->gallery->shell->r4->car->setCamera(&camera, window);

        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !keyPressed)
        {
            isNight = !isNight;
            keyPressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
        {
            keyPressed = false;
        }
        std::vector<SceneNode*> worldObjects;
        world->collectColliders(worldObjects);
        camera.update(worldObjects);
        //camera.update();
    //    camera.update(worldObjects); // pass world objects for collision
    //worldObjects.push_back(world); // recursively, or flatten tree and push nodes with colliders

        std::cout << "Colliders count: " << worldObjects.size() << std::endl;
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
        
        world->update(dt, camera.getPosition());

        renderer.drawAll(camera.getPosition());
        renderer.clear();

        if (isNight)
            nightSkybox.draw(view, projection);
        else
            skybox.draw(view, projection);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    AudioSystem::shutdown();
    return 0;
}