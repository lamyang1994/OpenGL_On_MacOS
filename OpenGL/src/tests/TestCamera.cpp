#include "Renderer.h"
#include "TestCamera.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

#include <math.h>
#include <stdio.h>

namespace test {

    TestCamera::TestCamera(GLFWwindow* window)
        :m_Model(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)), 
         m_Window(window), m_ClearColor(1.0f, 0.8f, 0.8f, 1.00f),
         m_FirstMouse(false), m_DeltaTime(0.0f), m_MousePosX(480.0f), m_MousePosY(360.0f)
    {
        float positions[] = {
             -0.7f, -0.7f,  0.7f, 0.0f, 0.0f,
              0.7f, -0.7f,  0.7f, 1.0f, 0.0f,
              0.7f,  0.7f,  0.7f, 1.0f, 1.0f,
             -0.7f,  0.7f,  0.7f, 0.0f, 1.0f,

              0.7f, -0.7f, -0.7f, 0.0f, 0.0f,
             -0.7f, -0.7f, -0.7f, 1.0f, 0.0f,
             -0.7f,  0.7f, -0.7f, 1.0f, 1.0f,
              0.7f,  0.7f, -0.7f, 0.0f, 1.0f,

             -0.7f,  0.7f,  0.7f, 0.0f, 0.0f,
              0.7f,  0.7f,  0.7f, 1.0f, 0.0f,
              0.7f,  0.7f, -0.7f, 1.0f, 1.0f,
             -0.7f,  0.7f, -0.7f, 0.0f, 1.0f,

              0.7f, -0.7f,  0.7f, 0.0f, 0.0f,
             -0.7f, -0.7f,  0.7f, 1.0f, 0.0f,
             -0.7f, -0.7f, -0.7f, 1.0f, 1.0f,
              0.7f, -0.7f, -0.7f, 0.0f, 1.0f,

              0.7f, -0.7f,  0.7f, 0.0f, 0.0f,
              0.7f, -0.7f, -0.7f, 1.0f, 0.0f,
              0.7f,  0.7f, -0.7f, 1.0f, 1.0f,
              0.7f,  0.7f,  0.7f, 0.0f, 1.0f,

             -0.7f, -0.7f, -0.7f, 0.0f, 0.0f,
             -0.7f, -0.7f,  0.7f, 1.0f, 0.0f,
             -0.7f,  0.7f,  0.7f, 1.0f, 1.0f,
             -0.7f,  0.7f, -0.7f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0,  1,  2,    0,  3,  2,
            4,  5,  6,    4,  7,  6,
            8,  9,  10,   8, 11, 10,
            12, 13, 14,  12, 15, 14,
            16, 17, 18,  16, 19, 18,
            20, 21, 22,  20, 23, 22
        };

        m_CubePositions = std::vector<glm::vec3>{
                glm::vec3(-2.0f, -2.0f,  -3.0f), 
                glm::vec3(-4.0f,  0.0f,  -4.5f), 
                glm::vec3(-2.0f,  2.0f,  -6.0f),  
                glm::vec3( 0.0f,  4.0f,  -7.5f),  
                glm::vec3( 2.0f,  2.0f,  -9.0f),  
                glm::vec3( 4.0f,  0.0f, -10.5f),  
                glm::vec3( 2.0f, -2.0f, -12.0f),  
                glm::vec3( 0.0f, -4.0f, -13.5f), 
                glm::vec3(-2.0f, -2.0f, -15.0f), 
                glm::vec3(-4.0f,  0.0f, -16.5f),
                glm::vec3(-2.0f,  2.0f, -18.0f),
                glm::vec3( 0.0f,  4.0f, -19.5f),
                glm::vec3( 2.0f,  2.0f, -21.0f),
                glm::vec3( 0.0f,  0.0f, -23.0f)
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));

        m_Camera = std::make_unique<Camera>();
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;

        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 36);

        m_Shader = std::make_unique<Shader>("../OpenGL/res/shader/BasicShader.glsl");
        m_Texture_A = std::make_unique<Texture>("../OpenGL/res/textures/dota2_logo.png");
        m_Texture_B = std::make_unique<Texture>("../OpenGL/res/textures/wood.png");

        // for(int i = 0; i < 14; i++)
        // {
        //     char tmp[1000];
        //     std::sprintf(tmp, "../OpenGL/res/textures/romantic_%d.jpg", i);
        //     m_Textures.push_back(std::make_unique<Texture>(tmp));
        // }

        m_Renderer = std::make_unique<Renderer>();  
        GLCall(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
        GLCall(glfwSetWindowUserPointer(m_Window, this));
        GLCall(glfwSetCursorPosCallback(m_Window, MouseMovement_Callback));
        GLCall(glfwSetScrollCallback(m_Window, MouseScroll_Callback));
    }   

    TestCamera::~TestCamera()
    {
        GLCall(glfwSetWindowUserPointer(m_Window, NULL));
        GLCall(glfwSetCursorPosCallback(m_Window, NULL));
    }

    void TestCamera::OnUpdate(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    void TestCamera::OnRender()
    {
        m_Renderer->Clear(m_ClearColor);

        m_Shader->Bind();
        m_Texture_A->Bind(0);
        m_Shader->SetUniform1i("u_Texture", 0);
        m_Texture_B->Bind(1);
        m_Shader->SetUniform1i("u_Texture_B", 1);

        ProcessInput();
        glm::mat4 view = m_Camera->GetViewMatrix();

        for (int i = 0; i < 14; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_CubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() + glm::radians(i*20.0f), glm::vec3(0.662f, 0.2f, 0.7222f));
            glm::mat4 proj = glm::perspective(m_Camera->GetZoom(), 960.0f / 720.0f, 0.1f, 100.0f);
            glm::mat4 mvp  = proj * view * model;

            // m_Textures[i]->Bind(i);
            // m_Shader->SetUniform1i("u_Texture", i);
 
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader); 
        }
    }

    void TestCamera::OnImGuiRender()
    {
        ImGui::SliderFloat("mouse position X", &m_MousePosX, 0.0f, 960.0f);
        ImGui::SliderFloat("mouse position Y", &m_MousePosY, 0.0f, 720.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    void TestCamera::ProcessInput()
    {
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            GLCall(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
            GLCall(glfwSetCursorPosCallback(m_Window, NULL));
        }

        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
            m_Camera->ProcessKeyboard(CameraMovement::FORWARD, m_DeltaTime);
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
            m_Camera->ProcessKeyboard(CameraMovement::BACKWARD, m_DeltaTime);
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
            m_Camera->ProcessKeyboard(CameraMovement::LEFT, m_DeltaTime);
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
            m_Camera->ProcessKeyboard(CameraMovement::RIGHT, m_DeltaTime);
    }

    void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y)
    {
        TestCamera* obj = (TestCamera*)glfwGetWindowUserPointer(window);
        if(obj->m_FirstMouse)
        {
            obj->m_MousePosX  = pos_x;
            obj->m_MousePosY  = pos_y;
            obj->m_FirstMouse = false;
        }
        double offset_x = pos_x - obj->m_MousePosX;
        double offset_y = obj->m_MousePosY - pos_y;
        obj->m_MousePosX = pos_x;
        obj->m_MousePosY = pos_y;

        obj->m_Camera->ProcessMouseMovement(offset_x, offset_y);
    }

    void MouseScroll_Callback(GLFWwindow* window, double offset_x, double offset_y)
    {
        TestCamera* obj = (TestCamera*)glfwGetWindowUserPointer(window);
        obj->m_Camera->ProcessMouseScroll(offset_y);
    }
} 


