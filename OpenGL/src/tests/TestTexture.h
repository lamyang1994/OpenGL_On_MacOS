#pragma once
#include <memory>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Test.h" 

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

namespace test {
    class TestTexture2D : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture_A;
        std::unique_ptr<Texture> m_Texture_B;
        std::unique_ptr<Renderer> m_Renderer;

        glm::mat4 m_Model, m_View, m_Proj;
        glm::vec3 m_Translate;
        glm::vec4 m_ClearColor;
        float m_Angle;
        bool m_Rolling;

    public:
        TestTexture2D();
        ~TestTexture2D() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };

    class TestTexture3D : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture_A;
        std::unique_ptr<Texture> m_Texture_B;
        std::unique_ptr<Renderer> m_Renderer;

        glm::mat4 m_Model, m_View, m_Proj;
        glm::vec3 m_Translate;
        glm::vec4 m_ClearColor;
        float m_Angle;
        bool m_Rolling;
        bool m_Magic;

    public:
        TestTexture3D();
        ~TestTexture3D() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };



} 