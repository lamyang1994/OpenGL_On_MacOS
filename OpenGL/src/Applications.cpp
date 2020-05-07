// #include <iostream>
// #include <string>
// #include <fstream>
// #include <sstream>

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// #include "vendor/glm/glm.hpp"
// #include "vendor/glm/gtc/matrix_transform.hpp"
// #include "vendor/imgui/imgui.h"
// #include "vendor/imgui/imgui_impl_opengl3.h"
// #include "vendor/imgui/imgui_impl_glfw.h"

// #include "Renderer.h"
// #include "VertexBuffer.h"
// #include "IndexBuffer.h"
// #include "VertexArray.h"
// #include "Shader.h"
// #include "Texture.h"

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
// }

// int main(void)
// {
//     GLFWwindow* window;

//     /* Initialize the library */
//     if (!glfwInit())
//         return -1;

//     // Define version and compatibility settings
//     const char* glsl_version = "#version 150";
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

//     /* Create a windowed mode window and its OpenGL context */
//     window = glfwCreateWindow(960, 720, "Lam's Window", NULL, NULL);
//     if (!window)
//     {
//         glfwTerminate();
//         return -1;
//     }
//     /* Make the window's context current */
//     glfwMakeContextCurrent(window);
//     // glfwSwapInterval(1);

//     glewExperimental = GL_TRUE;
//     if(glewInit() != GLEW_OK)
//     {
//         std::cout << "glewInit ERROR" << std::endl;
//         return -1;
//     }
//     std::cout<< "glVersion: " << glGetString(GL_VERSION) << std::endl;

//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // glfwGetFramebufferSize doesnt work

//     // float positions[] = {
//     //       0.0f,   0.0f, 0.0f, 0.0f,
//     //     100.0f,   0.0f, 1.0f, 0.0f,
//     //     100.0f, 100.0f, 1.0f, 1.0f,
//     //       0.0f, 100.0f, 0.0f, 1.0f
//     // };

//     float positions[] = {
//          -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
//           0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
//           0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
//          -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         
//           0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//          -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//          -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
//           0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

//          -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
//           0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
//           0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
//          -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,

//           0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
//          -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
//          -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//           0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

//           0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
//           0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//           0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
//           0.5f,  0.5f,  0.5f, 0.0f, 1.0f,

//          -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//          -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
//          -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
//          -0.5f,  0.5f, -0.5f, 0.0f, 1.0f
//     };

//     unsigned int indices[] = {
//         0, 1, 2,
//         0, 3, 2,
        
//         4, 5, 6,
//         4, 7, 6,

//         8, 9, 10,
//         8, 11, 10,

//         12, 13, 14,
//         12, 15, 14,

//         16, 17, 18,
//         16, 19, 18,

//         20, 21, 22,
//         20, 23, 22
//     };

//     GLCall(glEnable(GL_DEPTH_TEST));
//     GLCall(glEnable(GL_BLEND));
//     GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

//     VertexArray va;
//     VertexBuffer vb(positions, sizeof(positions));
//     VertexBufferLayout layout;

//     layout.Push<float>(3);
//     layout.Push<float>(2);
//     va.AddBuffer(vb, layout);
//     IndexBuffer ib(indices, 36);

//     Shader shader("../OpenGL/res/shader/BasicShader.glsl");
//     shader.Bind();

//     Texture texture("../OpenGL/res/textures/romantic.jpeg");
//     Texture texture_B("../OpenGL/res/textures/wood.png");

//     va.unBind();
//     vb.unBind();
//     ib.unBind();
//     shader.unBind();

//     Renderer renderer;

//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     ImGui::StyleColorsDark();
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init(glsl_version);

//     glm::vec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);
//     glm::vec3 Translate(0.0f, 0.0f, -3.0f);
//     float Angle = 0.0f;
//     bool Rolling = false, Magic;
//     /* Loop until the user closes the window */
//     while (!glfwWindowShouldClose(window))
//     {
//         renderer.Clear(clear_color);

//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();
//         {
//             ImGui::Begin("Control Table!");
//             ImGui::SliderFloat("Translation.X", &Translate.x,   -1.0f, 1.0f);
//             ImGui::SliderFloat("Translation.Y", &Translate.y,   -1.0f, 1.0f);
//             ImGui::SliderFloat("Translation.Z", &Translate.z, -100.0f, 0.0f);
//             ImGui::SliderFloat("Angle", &Angle, 0.0f, 360.0f);
//             ImGui::Checkbox("Rolling", &Rolling);
//             ImGui::Checkbox("Magic", &Magic);
//             ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

//             ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//             ImGui::End();
//         }

//         {
//             shader.Bind();
//             texture.Bind(0);
//             shader.SetUniform1i("u_Texture", 0);
//             texture_B.Bind(1);
//             shader.SetUniform1i("u_Texture_B", 1);

//             // glm::mat4(1.0f) : init the matrix to diagonal matrix
//             glm::mat4 model = glm::mat4(1.0f);
//             model = glm::translate(model, Translate);
//             if (Rolling)
//                 model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.662f, 0.2f, 0.7222f));
//             else
//                 model = glm::rotate(model, glm::radians(-Angle), glm::vec3(0.662f, 0.2f, 0.7222f));
            
//             // glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f);
//             glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);
//             glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//             glm::mat4 mvp = proj * view * model;

//             shader.SetUniformMat4f("u_MVP", mvp);
//             renderer.Draw(va, ib, shader); 
            
//             if (Magic)
//             {
//                 glm::vec3 cubePositions[] = {
//                     glm::vec3( 2.0f,  3.0f, -15.0f), 
//                     glm::vec3(-0.5f, -0.7f, -3.5f),  
//                     glm::vec3(-2.8f, -2.0f, -12.3f),  
//                     glm::vec3( 1.8f, -0.4f, -4.5f),  
//                     glm::vec3(-1.7f,  3.0f, -7.5f),  
//                     glm::vec3( 1.3f, -2.0f, -6.5f),  
//                     glm::vec3( 1.5f,  2.0f, -4.5f), 
//                     glm::vec3( 1.5f,  0.2f, -10.5f), 
//                     glm::vec3(-1.3f,  1.0f, -4.5f) 
//                 };
                
//                 for (int i = 0; i < 8; i++)
//                 {
//                     glm::mat4 model = glm::mat4(1.0f);
//                     model = glm::translate(model, cubePositions[i]);
//                     model = glm::rotate(model, (float)glfwGetTime() + glm::radians(i*20.0f), glm::vec3(0.662f, 0.2f, 0.7222f));
//                     glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);
//                     glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//                     glm::mat4 mvp = proj * view * model;

//                     shader.SetUniformMat4f("u_MVP", mvp);
//                     renderer.Draw(va, ib, shader); 
//                 }
//             }
//         }

//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//     // Cleanup
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     glfwDestroyWindow(window);
//     glfwTerminate();
    
//     return 0;
// }