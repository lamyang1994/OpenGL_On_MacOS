#pragma once

#include <string>
#include <unordered_map>

#include "vendor/glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void unBind() const;

    //Setting Uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const std::string& name, int value);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    ShaderProgramSource ParseShader(const std::string &fpath);
    unsigned int CreateShader(const std::string &vertextShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string source);
    int GetUniformLocation(const std::string& name);
};
