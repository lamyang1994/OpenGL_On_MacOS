#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "Shader.h"

Shader::Shader(const std::string& filepath)
    :m_RendererID(0), m_FilePath(filepath) 
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unBind() const
{
    GLCall(glUseProgram(0));
}

ShaderProgramSource Shader::ParseShader(const std::string &fpath)
{
    std::ifstream stream(fpath);

    enum class ShaderType
    {
        NONE = -1 , VERTEX = 0, FRAGMENT = 1
    };
    
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;

        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string &vertextShader, const std::string &fragmentShader)
{
    unsigned int p  = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    glValidateProgram(p);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);    
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //char message[length];
        char* message = (char*)alloca(length * sizeof(int));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " <<  (type == GL_VERTEX_SHADER ? "vertext" : "fragment") << " Shader!!" << std::endl;
        std::cout << message << std::endl;
        
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4fv(const std::string& name, glm::vec4 vec)
{
    GLCall(glUniform4fv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniform3fv(const std::string& name, glm::vec3 vec)
{
    GLCall(glUniform3fv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
{
    GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    else
        m_UniformLocationCache[name] = location;
    return location;
}