#include "TestModel.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

namespace test {

    TestModel::TestModel(GLFWwindow* window)
        : m_FirstMouse(true), m_DeltaTime(0.0f), m_MousePosX(480.0f), m_MousePosY(360.0f), m_Angle(0.0f),
          m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f)),
          m_Position(glm::vec3(0.0f, -10.0f, -20.0f)), m_Window(window)
    {
        m_Model = std::make_unique<Model>("../OpenGL/res/models/backpack/backpack.obj");
        m_Camera = std::make_unique<Camera>();

        m_Shader = std::make_shared<Shader>("../OpenGL/res/shader/ModelShader.glsl");
        m_Renderer = std::make_shared<Renderer>();

        GLCall(glfwSetWindowUserPointer(m_Window, this));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_DEPTH_TEST));
    }

    TestModel::~TestModel()
    {

    }

    void TestModel::OnUpdate(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

    void TestModel::OnRender()
    {
        m_Renderer->Clear();
        ProcessInput();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_Position);
        model = glm::rotate(model, glm::radians(m_Angle), glm::vec3(0.0f, 1.0f, 0.0f));

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Proj", m_Proj);
        m_Shader->SetUniformMat4f("u_View", m_Camera->GetViewMatrix());
        m_Shader->SetUniformMat4f("u_Model", model);
        m_Shader->SetUniformMat3f("u_NormalMatrix", glm::mat3(glm::transpose(glm::inverse(model))));
        m_Shader->SetUniform3fv("u_DirLight.lightDirection", glm::vec3(-1.0f, -1.0f, -1.0f));
        m_Shader->SetUniform3fv("u_DirLight.lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        m_Shader->SetUniform3fv("u_CameraPos", m_Camera->GetPos());
        m_Shader->SetUniform1f("u_Material.shininess", 0.088f * 128.0f);
        m_Model->Draw(*m_Renderer, *m_Shader);

    }

    void TestModel::OnImGuiRender()
    {
        ImGui::Text("Press Enter to Move, ESC to Stop!");
        ImGui::SliderFloat3("LightDirection", &m_Position.x, -500.0f, 0.0f);
        ImGui::SliderFloat("Angle", &m_Angle, 0.0f, 360.0f);
    }

    void TestModel::ProcessInput()
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
        TestModel* obj = (TestModel*)glfwGetWindowUserPointer(window);
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
}