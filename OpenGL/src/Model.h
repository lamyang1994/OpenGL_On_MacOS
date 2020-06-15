#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include "vendor/glm/glm.hpp"

#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct VertexInfo
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
}; 

struct TextureInfo 
{
    std::shared_ptr<Texture> texture;
    std::string Type;
};

class Mesh
{
public:
    Mesh(std::vector<VertexInfo> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures);
    ~Mesh();
    void Draw(Renderer& renderer, Shader& shader) const;

private:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;

    std::vector<VertexInfo> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<TextureInfo> m_Textures;

    void setupMesh();
};

class Model 
{
public:
    Model(const std::string& path);
    ~Model();
    void Draw(Renderer& renderer, Shader& shader) const;

private:
    std::vector<Mesh> m_Meshes;
    std::string m_FilePath;
    std::string m_Directory;
    std::unordered_map<std::string, TextureInfo> m_TextureInfoCache;
    
    void loadModel();
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<TextureInfo> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
};