#include "TestTexture.h"
#include "Renderer.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

namespace test {
    /*-----------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------- TEXTURE 2D --------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    TestTexture2D::TestTexture2D()
        :m_Model(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
         m_Translate(0.0f, 0.0f, 0.0f), m_ClearColor(1.0f, 0.8f, 0.8f, 1.00f),
         m_Angle(0.0f), m_Rolling(false)
    {
        float positions[] = {
              0.0f,   0.0f, 0.0f, 0.0f, 0.0f,
            200.0f,   0.0f, 0.0f, 1.0f, 0.0f,
            200.0f, 200.0f, 0.0f, 1.0f, 1.0f,
              0.0f, 200.0f, 0.0f, 0.0f, 1.0f
            };

        unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2,
        };
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;

        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("../OpenGL/res/shader/BasicShader.glsl");
        m_Texture_A = std::make_unique<Texture>("../OpenGL/res/textures/romantic.jpeg");
        m_Texture_B = std::make_unique<Texture>("../OpenGL/res/textures/wood.png");

        m_Renderer = std::make_unique<Renderer>();
    }   

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {
    }

    void TestTexture2D::OnRender()
    {
        m_Renderer->Clear(m_ClearColor);

        m_Shader->Bind();
        m_Texture_A->Bind(0);
        m_Shader->SetUniform1i("u_Texture", 0);
        m_Texture_B->Bind(1);
        m_Shader->SetUniform1i("u_Texture_B", 1);

        glm::mat4 model = glm::translate(m_Model, m_Translate);
        if (m_Rolling)
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        else
            model = glm::rotate(model, glm::radians(-m_Angle), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader); 
    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat("Translation.X", &m_Translate.x,   0.0f, 960.0f);
        ImGui::SliderFloat("Translation.Y", &m_Translate.y,   0.0f, 720.0f);
        ImGui::SliderFloat("Translation.Z", &m_Translate.z, -100.0f, 0.0f);
        ImGui::SliderFloat("Angle", &m_Angle, 0.0f, 360.0f);
        ImGui::Checkbox("Rolling", &m_Rolling);
        ImGui::ColorEdit3("clear color", (float*)&m_ClearColor); // Edit 3 floats representing a color

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }


    /*-----------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------- TEXTURE 3D --------------------------------------------*/
    /*-----------------------------------------------------------------------------------------------------*/
    TestTexture3D::TestTexture3D()
        :m_Model(glm::mat4(1.0f)), m_View(glm::mat4(1.0f)), m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)),
         m_Translate(0.0f, 0.0f, -3.0f), m_ClearColor(1.0f, 0.8f, 0.8f, 1.00f),
         m_Angle(0.0f), m_Rolling(false), m_Magic(false)
    {
        float positions[] = {
             -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
              0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
              0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
             -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

              0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
             -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
             -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
              0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

             -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
              0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
              0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

              0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
             -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
             -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
              0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

              0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
              0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
              0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
              0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
             -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
             -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2,

            4, 5, 6,
            4, 7, 6,

            8, 9, 10,
            8, 11, 10,

            12, 13, 14,
            12, 15, 14,

            16, 17, 18,
            16, 19, 18,

            20, 21, 22,
            20, 23, 22
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;

        layout.Push<float>(3);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 36);

        m_Shader = std::make_unique<Shader>("../OpenGL/res/shader/BasicShader.glsl");
        m_Texture_A = std::make_unique<Texture>("../OpenGL/res/textures/romantic.jpeg");
        m_Texture_B = std::make_unique<Texture>("../OpenGL/res/textures/wood.png");

        m_Renderer = std::make_unique<Renderer>();
    }   

    TestTexture3D::~TestTexture3D()
    {
    }

    void TestTexture3D::OnUpdate(float deltaTime)
    {
    }

    void TestTexture3D::OnRender()
    {
        m_Renderer->Clear(m_ClearColor);

        m_Shader->Bind();
        m_Texture_A->Bind(0);
        m_Shader->SetUniform1i("u_Texture", 0);
        m_Texture_B->Bind(1);
        m_Shader->SetUniform1i("u_Texture_B", 1);

        glm::mat4 model = glm::translate(m_Model, m_Translate);
        if (m_Rolling)
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.662f, 0.2f, 0.7222f));
        else
            model = glm::rotate(model, glm::radians(-m_Angle), glm::vec3(0.662f, 0.2f, 0.7222f));
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader); 
        if (m_Magic)
        {
            glm::vec3 cubePositions[] = {
                glm::vec3( 2.0f,  3.0f, -15.0f), 
                glm::vec3(-0.5f, -0.7f, -3.5f),  
                glm::vec3(-2.8f, -2.0f, -12.3f),  
                glm::vec3( 1.8f, -0.4f, -4.5f),  
                glm::vec3(-1.7f,  3.0f, -7.5f),  
                glm::vec3( 1.3f, -2.0f, -6.5f),  
                glm::vec3( 1.5f,  2.0f, -4.5f), 
                glm::vec3( 1.5f,  0.2f, -10.5f), 
                glm::vec3(-1.3f,  1.0f, -4.5f) 
            };
         
            for (int i = 0; i < 9; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, (float)glfwGetTime() + glm::radians(i*20.0f), glm::vec3(0.662f, 0.2f, 0.7222f));
                glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);
                glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
                glm::mat4 mvp = proj * view * model;
 
                m_Shader->SetUniformMat4f("u_MVP", mvp);
                m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader); 
            }
        }
    }

    void TestTexture3D::OnImGuiRender()
    {
        ImGui::SliderFloat("Translation.X", &m_Translate.x,   -1.0f, 1.0f);
        ImGui::SliderFloat("Translation.Y", &m_Translate.y,   -1.0f, 1.0f);
        ImGui::SliderFloat("Translation.Z", &m_Translate.z, -100.0f, 0.0f);
        ImGui::SliderFloat("Angle", &m_Angle, 0.0f, 360.0f);
        ImGui::Checkbox("Rolling", &m_Rolling);
        ImGui::Checkbox("Magic", &m_Magic);
        ImGui::ColorEdit3("clear color", (float*)&m_ClearColor); // Edit 3 floats representing a color

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
} 

