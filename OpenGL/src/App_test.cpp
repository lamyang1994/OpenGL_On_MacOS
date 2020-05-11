#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture.h"
#include "tests/TestCamera.h"
#include "tests/TestLight.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Define version and compatibility settings
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 720, "Lam's Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "glewInit ERROR" << std::endl;
        return -1;
    }
    std::cout<< "glVersion: " << glGetString(GL_VERSION) << std::endl;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // glfwGetFramebufferSize doesnt work

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
    testMenu->RegisterTest<test::TestTexture3D>("3D Texture");
    testMenu->RegisterTest<test::TestCamera>("Camera", window);
    testMenu->RegisterTest<test::TestLight>("Light");

    float deltaTime = 0.0f;
    float lastTime  = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;    
        lastTime = currentTime;
        renderer.Clear({ 0.45f, 0.55f, 0.60f, 1.00f });

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentTest)
        {
            currentTest->OnUpdate(deltaTime);
            currentTest->OnRender();
            ImGui::Begin("TEST");
            if ( currentTest != testMenu && ImGui::Button("<-") )
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}