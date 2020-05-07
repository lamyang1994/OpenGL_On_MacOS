#pragma once

#include "Test.h" 

namespace test {
    class TestClearColor : public Test
    {
    private:
        float m_ClearColor[4];

    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
} 