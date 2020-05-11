#include "TestLight.h"

namespace test{
    TestLight::TestLight()
        :m_ObjectPos(0.0f, 0.0f, -4.0f), m_LightPos(3.6f, 3.0f, -10.0f), m_ObjectColor(1.0f, 0.5f, 0.31f, 1.0f), m_LightColor(1.0f, 1.0f, 1.0f, 1.0f),
         m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)), m_View(glm::mat4(1.0f))
    {
        float positions[] = {
             -0.5f, -0.5f,  0.5f,
              0.5f, -0.5f,  0.5f,
              0.5f,  0.5f,  0.5f,
             -0.5f,  0.5f,  0.5f,

             -0.5f, -0.5f, -0.5f,
              0.5f, -0.5f, -0.5f,
              0.5f,  0.5f, -0.5f,
             -0.5f,  0.5f, -0.5f,
        };

        unsigned int indices[] = {
            0, 1, 2,    0, 3, 2,
            1, 5, 6,    1, 2, 6,
            4, 5, 6,    4, 7, 6,
            4, 0, 3,    4, 7, 3,
            3, 2, 6,    3, 7, 6,
            0, 1, 5,    0, 4, 5
        };

        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(3);

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 36);

        m_ObjectShader = std::make_unique<Shader>("../OpenGL/res/shader/ObjectShader.glsl");
        m_LightShader = std::make_unique<Shader>("../OpenGL/res/shader/LightShader.glsl");

        m_Renderer = std::make_unique<Renderer>();

    }

    TestLight::~TestLight()
    {

    }

    void TestLight::OnUpdate(float deltaTime)
    {
    }

    void TestLight::OnRender()
    {
        m_Renderer->Clear();
        // draw light
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_LightPos);
            model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.662f, 0.2f, 0.7222f));
            m_LightShader->Bind();
            glm::mat4 mvp = m_Proj * m_View * model;
            m_LightShader->SetUniformMat4f("u_MVP", mvp);
            m_LightShader->SetUniform4f("u_LightColor", m_LightColor);
            m_Renderer->Draw(*m_VAO, *m_IBO, *m_LightShader);

        }
        // draw object
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_ObjectPos);
            model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0.662f, 0.2f, 0.7222f));

            m_ObjectShader->Bind();
            glm::mat4 mvp = m_Proj * m_View * model;
            m_ObjectShader->SetUniformMat4f("u_MVP", mvp);
            m_ObjectShader->SetUniform4f("u_LightColor", m_LightColor);
            m_ObjectShader->SetUniform4f("u_ObjectColor", m_ObjectColor);
            m_Renderer->Draw(*m_VAO, *m_IBO, *m_ObjectShader);

        }
        
    }

    void TestLight::OnImGuiRender()
    {

    }

};