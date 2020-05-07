#include "Test.h"
#include "vendor/imgui/imgui.h"

namespace test{
    TestMenu::TestMenu(Test*& CurrentTestPointer) 
        :m_CurrentTest(CurrentTestPointer)
    {
    }

    void TestMenu::OnImGuiRender()
    {
        for (auto& test : m_Tests)
            if (ImGui::Button(test.first.c_str()))
                m_CurrentTest = test.second();
            
    }
}