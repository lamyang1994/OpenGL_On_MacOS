#pragma once

#include <assert.h>
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "vendor/glm/glm.hpp"

#define GLCall(x) GLClearError(); x; assert(GLLogError(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogError(const char* function, const char* file, const int line);

class Renderer
{
public:
    void Clear() const;
    void Clear(const glm::vec4& clear_color) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
