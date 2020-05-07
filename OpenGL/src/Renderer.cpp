#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] " << error  << " (hex = "<< std::hex << error << ") " <<
                        "in function: " << function << ", file: " << file << ", line: " << std::dec << line << std::endl;
        return false;
    }
    return true;
}


void Renderer::Clear() const 
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
void Renderer::Clear(const glm::vec4& clear_color) const 
{
    GLCall(glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
    // GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}