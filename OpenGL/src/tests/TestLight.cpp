#include "TestLight.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

namespace test{
    TestLight::TestLight()
        :m_ObjectPos(3.0f, 3.0f, 0.0f), m_LightPos(0.0f, 0.0f, 0.0f), m_CameraPos(0.0f, 0.0f, 1.0f), m_LightColor(1.0f, 1.0f, 1.0f),
         m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)), m_View(glm::mat4(1.0f)), m_CameraAngle(0.0f)
    {
        // float positions[] = {
        //      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
        //       0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        //       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
        //      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,

        //      -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        //       0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        //       0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
        //      -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f
        // };

        // unsigned int indices[] = {
        //     0, 1, 2,    0, 3, 2,
        //     1, 5, 6,    1, 2, 6,
        //     5, 4, 7,    5, 6, 7,
        //     7, 3, 0,    7, 4, 0,
        //     3, 2, 6,    3, 7, 6,
        //     4, 5, 1,    4, 0, 1
        // };

        float positions[] = {
             -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
              0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
             -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

              0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
             -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
             -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
              0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,

              0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
              0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

              0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
              0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

             -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
             -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
             -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f
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

        GLCall(glEnable(GL_DEPTH_TEST));

        m_VBO = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 36);

        m_ObjectShader = std::make_unique<Shader>("../OpenGL/res/shader/ObjectShader.glsl");
        m_LightShader = std::make_unique<Shader>("../OpenGL/res/shader/LightShader.glsl");

        m_Texture_0 = std::make_unique<Texture>("../OpenGL/res/textures/container.png");
        m_Texture_1 = std::make_unique<Texture>("../OpenGL/res/textures/container_specular.png");
        m_Texture_2 = std::make_unique<Texture>("../OpenGL/res/textures/matrix.jpg");

        m_Renderer = std::make_unique<Renderer>();
        GLCall(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION));
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

        // camera 
        {
            float camX = glm::sin(glm::radians(m_CameraAngle)) * 10.0f;
            float camZ = glm::cos(glm::radians(m_CameraAngle)) * 10.0f;
            m_CameraPos = glm::vec3(camX, 0.0, camZ);
            m_View = glm::lookAt(m_CameraPos, m_LightPos, glm::vec3(0.0f, 1.0f, 0.0f)); 
        }

        // draw light
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_LightPos);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.662f, 0.2f, 0.7222f));
            m_LightShader->Bind();
            m_LightShader->SetUniformMat4f("u_MVP", m_Proj * m_View * model);
            m_LightShader->SetUniform3fv("u_LightColor", m_LightColor);
            m_Renderer->Draw(*m_VAO, *m_IBO, *m_LightShader);
        }
        // draw object
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_ObjectPos);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.662f, 0.2f, 0.7222f));

            m_ObjectShader->Bind();
            m_ObjectShader->SetUniformMat4f("u_Proj", m_Proj);
            m_ObjectShader->SetUniformMat4f("u_View", m_View);
            m_ObjectShader->SetUniformMat4f("u_Model", model);
            m_ObjectShader->SetUniformMat3f("u_NormalMatrix", glm::mat3(glm::transpose(glm::inverse(model))));

            m_ObjectShader->SetUniform3fv("u_CameraPos", m_CameraPos);

            m_ObjectShader->SetUniform3fv("u_Light.position", m_LightPos);
            m_ObjectShader->SetUniform3fv("u_Light.ambient",  0.2f * m_LightColor);
            m_ObjectShader->SetUniform3fv("u_Light.diffuse",  0.5f * m_LightColor);
            m_ObjectShader->SetUniform3fv("u_Light.specular", m_LightColor);

            m_Texture_0->Bind(0);
            m_ObjectShader->SetUniform1i("u_Material.diffuse",  0);
            m_Texture_1->Bind(1);
            m_ObjectShader->SetUniform1i("u_Material.specular",  1);
            m_Texture_2->Bind(2);
            m_ObjectShader->SetUniform1i("u_Material.ambient",  2);
            m_ObjectShader->SetUniform1f("u_Material.shininess", m_Shininess);

            m_Renderer->Draw(*m_VAO, *m_IBO, *m_ObjectShader);

        }
    }

    void TestLight::OnImGuiRender()
    {
        ImGui::SliderFloat("Camera Angle", &m_CameraAngle,    0.0f,   360.0f);
        ImGui::SliderFloat3("ObjectPos" ,  &m_ObjectPos.x,    -20.0f, 20.0f);
        ImGui::SliderFloat("shininess",    &m_Shininess,      0.0f,   128.0f);

    }

};