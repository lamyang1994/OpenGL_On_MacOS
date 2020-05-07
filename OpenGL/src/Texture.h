#pragma once

#include "Renderer.h"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string&);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void unBind() const;
    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
};