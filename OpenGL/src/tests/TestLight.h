#pragma once
#include "Test.h"
#include "Camera.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


namespace test{
    static void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y);

    class TestLight : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_LightShader;
        std::unique_ptr<Shader> m_ObjectShader;
        std::unique_ptr<Renderer> m_Renderer;
        std::unique_ptr<Texture> m_Texture_0;
        std::unique_ptr<Texture> m_Texture_1;
        // std::unique_ptr<Texture> m_Texture_2;
        std::vector<glm::vec3> m_CubePositions;

        //light
        glm::vec4 m_LightVec;
        glm::vec3 m_LightColor;
        float m_Shininess, m_Constant, m_Linear, m_Quadratic;

        //camera
        std::unique_ptr<Camera> m_Camera;
        bool m_FlashLight, m_FirstMouse;
        float m_DeltaTime, m_MousePosX, m_MousePosY;

        glm::mat4 m_Proj;
        GLFWwindow* m_Window;

    public:
        TestLight(GLFWwindow*);
        ~TestLight() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        friend void MouseMovement_Callback(GLFWwindow* window, double pos_x, double pos_y);

    private:
        void ProcessInput();
    };

}