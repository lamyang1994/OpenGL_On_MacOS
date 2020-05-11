#pragma once

#include "Test.h" 
#include "Camera.h"

namespace test {
 
    class TestCamera : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture_A;
        std::unique_ptr<Texture> m_Texture_B;
        std::unique_ptr<Renderer> m_Renderer;
        // std::vector<std::unique_ptr<Texture>> m_Textures;
        std::vector<glm::vec3> m_CubePositions;
        std::unique_ptr<Camera> m_Camera;

        glm::mat4 m_Model, m_View, m_Proj;
        GLFWwindow* m_Window;
        glm::vec4 m_ClearColor;
        bool m_FirstMouse;
        float m_DeltaTime, m_MousePosX, m_MousePosY;

    public:
        TestCamera(GLFWwindow* window);
        ~TestCamera() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        friend void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y);
        friend void MouseScroll_Callback(GLFWwindow* window, double offset_x, double offset_y);

    private:
        void ProcessInput();
    };
} 