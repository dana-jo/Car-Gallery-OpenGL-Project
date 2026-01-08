#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "core/Shader.h"
#include "core/Renderer.h"
#include "objects/Box.h"
#include "graphics/Texture.h"
#include "graphics/Skybox.h"
#include "graphics/Material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Camera.h>

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
    Shader shader("shaders/mesh_shader.vert", "shaders/mesh_shader.frag");

    Renderer renderer;
    renderer.shader = shader;

    // --------------------------------------------------------
    // Textures
    // --------------------------------------------------------
    Texture brickTex("assets/textures/brick.jpg");          // RGB
    Texture windowTex("assets/textures/blue_transparent.png");        // RGBA (transparent)

    // --------------------------------------------------------
    // Materials
    // --------------------------------------------------------
    Material brickMat(&brickTex, { 2.0f, 2.0f });  // tiled
    Material windowMat(&windowTex, { 1.0f, 1.0f }); // transparent

    // --------------------------------------------------------
    // Objects
    // --------------------------------------------------------

    // ---- Test 1: Opaque box ----
    Box opaqueBox(1.0f, 1.0f, 1.0f);
    opaqueBox.position = { -1.5f, 0.0f, -2.0f };
    opaqueBox.setMaterial(&brickMat);

    // ---- Test 2: Back box (opaque) ----
    Box backBox(1.0f, 1.0f, 1.0f);
    backBox.position = { 1.0f, 0.0f, -3.5f };
    backBox.setMaterial(&brickMat);

    // ---- Test 2: Front transparent box (window) ----
    Box windowBox(1.0f, 1.0f, 0.1f);
    windowBox.position = { 1.0f, 0.0f, -2.5f };
    windowBox.setMaterial(&windowMat); // marks node as transparent

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

        renderer.submit(&opaqueBox);
        renderer.submit(&backBox);
        renderer.submit(&windowBox);

        renderer.drawAll(camera.getPosition());
        renderer.clear();

        skybox.draw(view, projection);

        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}