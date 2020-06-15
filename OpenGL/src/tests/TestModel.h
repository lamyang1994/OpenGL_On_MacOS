#pragma once

#include "Test.h"
#include "Model.h"
#include "Camera.h"

namespace test {

    static void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y);

    class TestModel : public Test
    {
    public:
        TestModel(GLFWwindow* window);
        ~TestModel() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        friend void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y);
    private:
        std::unique_ptr<Model> m_Model;
        std::shared_ptr<Renderer> m_Renderer;
        std::shared_ptr<Shader> m_Shader;

        //camera
        std::unique_ptr<Camera> m_Camera;
        bool m_FirstMouse;
        float m_DeltaTime, m_MousePosX, m_MousePosY, m_Angle;

        glm::mat4 m_Proj;
        glm::vec3 m_Position;
        GLFWwindow* m_Window;

    private:
        void ProcessInput();

    };
}
