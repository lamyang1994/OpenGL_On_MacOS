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
    Texture(const std::string& fpath, bool isMipmap = true);
    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void unBind() const;
    
    // inline unsigned int GetID() const { return m_RendererID; }
    inline std::string GetPath() const { return m_FilePath; }
    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
};