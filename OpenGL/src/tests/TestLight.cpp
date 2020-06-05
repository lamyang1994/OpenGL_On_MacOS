#include "TestLight.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

namespace test{

    TestLight::TestLight(GLFWwindow* window)
        :m_LightDir(-1.0f, -1.0f, 0.0f), m_LightColor(1.0f, 1.0f, 1.0f),
         m_Shininess(0.088f * 128.0f), m_Linear(0.045f), m_Quadratic(0.0075f),
         m_isDirLight(1), m_isSpotLight(1), m_numPointLight(4),
         m_FirstMouse(true), m_DeltaTime(0.0f), m_MousePosX(480.0f), m_MousePosY(360.0f),
         m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)),
         m_Window(window)
    {

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
            0,  1,  2,    0,  3,  2,
            4,  5,  6,    4,  7,  6,
            8,  9,  10,   8,  11, 10,
            12, 13, 14,   12, 15, 14,
            16, 17, 18,   16, 19, 18,
            20, 21, 22,   20, 23, 22
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

        m_LightPositions = std::vector<glm::vec3>{
                glm::vec3( 0.0f,  0.0f,  -0.0f), 
                glm::vec3( 3.0f,  3.0f,  -8.0f), 
                glm::vec3( -3.0f, 3.0f,  -16.0f), 
                glm::vec3( 4.0f,  4.0f,  -24.0f)  
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
        // m_Texture_2 = std::make_unique<Texture>("../OpenGL/res/textures/matrix.jpg");

        m_Renderer = std::make_unique<Renderer>();
        // GLCall(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION));
        m_Camera = std::make_unique<Camera>();
        GLCall(glfwSetWindowUserPointer(m_Window, this));
    }

    TestLight::~TestLight()
    {

    }

    void TestLight::OnUpdate(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    void TestLight::OnRender()
    {
        m_Renderer->Clear();
        ProcessInput();
        // draw light
        for (int i = 0; i < m_numPointLight; i++)
        {

            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_LightPositions[i]);
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.662f, 0.2f, 0.7222f));
            model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
            m_LightShader->Bind();
            m_LightShader->SetUniformMat4f("u_MVP", m_Proj * m_Camera->GetViewMatrix() * model);
            m_LightShader->SetUniform3fv("u_LightColor", m_LightColor);
            m_Renderer->Draw(*m_VAO, *m_IBO, *m_LightShader);
        }

        m_ObjectShader->Bind();
        m_ObjectShader->SetUniformMat4f("u_Proj", m_Proj);
        m_ObjectShader->SetUniformMat4f("u_View", m_Camera->GetViewMatrix());

        //texture
        m_Texture_0->Bind(0);
        m_ObjectShader->SetUniform1i("u_Material.diffuse",  0);
        m_Texture_1->Bind(1);
        m_ObjectShader->SetUniform1i("u_Material.specular",  1);
        // m_Texture_2->Bind(2);
        // m_ObjectShader->SetUniform1i("u_Material.ambient",  2);
        m_ObjectShader->SetUniform1f("u_Material.shininess", m_Shininess);

        //Direction Light
        m_ObjectShader->SetUniform3fv("u_DirLight.lightDirection", m_LightDir);
        m_ObjectShader->SetUniform3fv("u_DirLight.lightColor", m_LightColor);

        //Spot Light
        m_ObjectShader->SetUniform3fv("u_SpotLight.lightPosition", m_Camera->GetPos());
        m_ObjectShader->SetUniform3fv("u_SpotLight.lightColor", m_LightColor);
        m_ObjectShader->SetUniform1f("u_SpotLight.constant", 1.0f);
        m_ObjectShader->SetUniform1f("u_SpotLight.linear", 0.5 * m_Linear);
        m_ObjectShader->SetUniform1f("u_SpotLight.quadratic", 0.5 * m_Quadratic);
        m_ObjectShader->SetUniform3fv("u_SpotLight.spotDir", m_Camera->GetFront());
        m_ObjectShader->SetUniform1f("u_SpotLight.cutOff", glm::cos(glm::radians(10.0f)));
        m_ObjectShader->SetUniform1f("u_SpotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        //Point Lights
        for (int i = 0; i < 4; i++)
        {
            char u_name[100];
            std::sprintf(u_name, "u_PointLights[%d].lightPosition", i);
            m_ObjectShader->SetUniform3fv(u_name, m_LightPositions[i]);

            std::sprintf(u_name, "u_PointLights[%d].lightColor", i);
            m_ObjectShader->SetUniform3fv(u_name, m_LightColor);

            std::sprintf(u_name, "u_PointLights[%d].constant", i);
            m_ObjectShader->SetUniform1f(u_name, 1.0f);

            std::sprintf(u_name, "u_PointLights[%d].linear", i);
            m_ObjectShader->SetUniform1f(u_name, m_Linear);

            std::sprintf(u_name, "u_PointLights[%d].quadratic", i);
            m_ObjectShader->SetUniform1f(u_name, m_Quadratic);
        }

        //control uniform
        m_ObjectShader->SetUniform3fv("u_CameraPos", m_Camera->GetPos());
        m_ObjectShader->SetUniform1i("u_isDirLight", (int)m_isDirLight);
        m_ObjectShader->SetUniform1i("u_isSpotLight", (int)m_isSpotLight);
        m_ObjectShader->SetUniform1i("u_numPointLight", m_numPointLight);
        
        //draw
        for (int i = 0; i < 14; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_CubePositions[i]);
            model = glm::rotate(model, glm::radians(i*20.0f), glm::vec3(0.662f, 0.2f, 0.7222f));

            m_ObjectShader->SetUniformMat4f("u_Model", model);
            m_ObjectShader->SetUniformMat3f("u_NormalMatrix", glm::mat3(glm::transpose(glm::inverse(model))));

            m_Renderer->Draw(*m_VAO, *m_IBO, *m_ObjectShader); 
        }
    }

    void TestLight::OnImGuiRender()
    {
        ImGui::Text("Press Enter to Move, ESC to Stop!");

        ImGui::SliderFloat3("LightDirection",   &m_LightDir.x,   -1.0f, 1.0f);
        ImGui::SliderFloat("Shininess",    &m_Shininess,      0.0f,   128.0f);
        ImGui::SliderFloat("LightLinear",    &m_Linear,       0.0f,   0.1f);
        ImGui::SliderFloat("LightQuadratic", &m_Quadratic,    0.0f,   0.1f);

        ImGui::Checkbox("Direction Light", &m_isDirLight);
        ImGui::Checkbox("Spot Light", &m_isSpotLight);
        ImGui::SliderInt("Point Lights", &m_numPointLight, 0, 4);
    }
    
    void TestLight::ProcessInput()
    {
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            GLCall(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
            GLCall(glfwSetCursorPosCallback(m_Window, NULL));
        }

        if (glfwGetKey(m_Window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            GLCall(glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
            GLCall(glfwSetCursorPosCallback(m_Window, MouseMovement_Callback));
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
        TestLight* obj = (TestLight*)glfwGetWindowUserPointer(window);
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

};