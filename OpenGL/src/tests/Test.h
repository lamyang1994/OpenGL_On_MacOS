#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>


namespace test {
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu: public Test
    {
    public:
        TestMenu(Test*& CurrentTestPointer);
        void OnImGuiRender() override;

        template<typename T, typename ...Args>
        void RegisterTest(const std::string& name, Args&& ...args)
        {
            std::cout << "Register Test " << name << std::endl;
            m_Tests.push_back(std::make_pair(name, [&]() { return new T(std::forward<Args>(args)...); }));
        }

    private:
        Test*& m_CurrentTest;   
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

    };
}