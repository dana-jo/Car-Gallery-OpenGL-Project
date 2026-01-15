#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Shader.h"
#include "core/Renderer.h"
#include "objects/Box.h"
#include "graphics/Texture.h"
#include "graphics/Skybox.h"
#include "graphics/Material.h"
#include "objects/Polygon.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Camera.h>
#include <Model.h>

// ------------------------------------------------------------
// Simple camera values
// ------------------------------------------------------------

glm::mat4 getProjection(int w, int h)
{
    return glm::perspective(
        glm::radians(60.0f),
        (float)w / (float)h,
        0.1f,
        100.0f
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

    // --------------------------------------------------------
    // Shader
    // --------------------------------------------------------
    Shader shader("shaders/light_shader.vert", "shaders/light_shader.frag");

    Renderer renderer;
    renderer.shader = shader;

    // --------------------------------------------------------
    // Textures
    // --------------------------------------------------------
    Texture blueTex("assets/textures/brick.jpg");

    // --------------------------------------------------------
    // Materials
    // --------------------------------------------------------
    Material blueMat(&blueTex, { 1.0f, 1.0f });

    // --------------------------------------------------------
    // Objects
    // --------------------------------------------------------
    Model model("assets/pine/scrubPine.obj");
    model.position = { 0.0f, -1.0f, -3.0f };
    model.scale = { 0.005f, 0.005f, 0.005f };

    // ---- Test 1: Opaque box ----
    std::vector<glm::vec2> star = {
    { 0.0f,  1.2f},
    { 0.3f,  0.3f},
    { 1.2f,  0.0f},
    { 0.3f, -0.3f},
    { 0.0f, -1.2f},
    {-0.3f, -0.3f},
    {-1.2f,  0.0f},
    {-0.3f,  0.3f}
    };

	std::reverse(star.begin(), star.end());

    Polygon wall = Polygon(star, 1.0f);
    wall.position = { 0, 1, -5 };
    wall.setMaterial(&blueMat);

    Skybox skybox({
    "assets/skybox/right.jpg",
    "assets/skybox/left.jpg",
    "assets/skybox/top.jpg",
    "assets/skybox/bottom.jpg",
    "assets/skybox/front.jpg",
    "assets/skybox/back.jpg"
        });

    // --------------------------------------------------------
    // Render loop
    // --------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        camera.update();

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getView();
        glm::mat4 projection = getProjection(1280, 720);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

		shader.setVec3("viewPos", camera.getPosition());

		shader.setFloat("material_shininess", 32.0f);

        shader.setVec3("dirLight.direction", glm::vec3(-0.3f, -1.0f, -0.2f));
        shader.setVec3("dirLight.ambient", glm::vec3(0.1f));
        shader.setVec3("dirLight.diffuse", glm::vec3(0.7f));
        shader.setVec3("dirLight.specular", glm::vec3(0.2f));
        shader.setBool("dirLight.enabled", true);

        shader.setInt("numSpotLights", 1);

        shader.setVec3("spotLights[0].position", camera.getPosition());
        shader.setVec3("spotLights[0].direction", glm::vec3(0, 0, -1));

        shader.setFloat("spotLights[0].cutOff",
            glm::cos(glm::radians(12.5f)));
        shader.setFloat("spotLights[0].outerCutOff",
            glm::cos(glm::radians(17.5f)));

        shader.setVec3("spotLights[0].ambient", glm::vec3(0.0f));
        shader.setVec3("spotLights[0].diffuse", glm::vec3(1.0f));
        shader.setVec3("spotLights[0].specular", glm::vec3(0.5f));

        shader.setFloat("spotLights[0].constant", 1.0f);
        shader.setFloat("spotLights[0].linear", 0.09f);
        shader.setFloat("spotLights[0].quadratic", 0.032f);

        shader.setBool("spotLights[0].enabled", true);

        shader.setInt("numPointLights", 0);

        renderer.submit(&model);
		//renderer.submit(&box);

		//renderer.submit(&wall);

        renderer.drawAll(camera.getPosition());
        renderer.clear();

        //skybox.draw(view, projection);

        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}