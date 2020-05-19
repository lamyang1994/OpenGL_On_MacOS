#include "Test.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


namespace test{

    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        Material()
            : ambient(0.25f, 0.20725f, 0.20725f), diffuse(1.0f, 0.829f, 0.829f), specular(0.296648f, 0.296648f, 0.296648f), shininess(0.088f * 128.0f)
        {
        }

    };

    class TestLight : public Test
    {
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_LightShader;
        std::unique_ptr<Shader> m_ObjectShader;
        std::unique_ptr<Renderer> m_Renderer;

        glm::vec3 m_ObjectPos, m_LightPos, m_CameraPos;
        glm::vec3 m_LightColor;
        Material m_Material;

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