#include "Test.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


namespace test{

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
        std::unique_ptr<Texture> m_Texture_2;

        glm::vec3 m_ObjectPos, m_LightPos, m_CameraPos;
        glm::vec3 m_LightColor;
        float m_Shininess = 0.088f * 128.0f;

        glm::mat4 m_Proj, m_View;

        float m_CameraAngle;
        

    public:
        TestLight();
        ~TestLight() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    };

}