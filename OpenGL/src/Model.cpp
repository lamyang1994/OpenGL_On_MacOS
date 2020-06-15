#include "Model.h"

/*-------------------------------------------------------------*/
/*                       Mesh                                  */
/*-------------------------------------------------------------*/
Mesh::Mesh(std::vector<VertexInfo> vertices, std::vector<unsigned int> indices, std::vector<TextureInfo> textures)
{
    m_Vertices = vertices;
    m_Indices = indices;
    m_Textures = textures;

    setupMesh();
}
Mesh::~Mesh()
{

}

void Mesh::setupMesh()
{
    m_VAO = std::make_shared<VertexArray>();
    m_VBO = std::make_shared<VertexBuffer>(&m_Vertices[0], m_Vertices.size() * sizeof(VertexInfo));
    m_IBO = std::make_shared<IndexBuffer>(&m_Indices[0], m_Indices.size());
    
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    m_VAO->AddBuffer(*m_VBO, layout);
}

void Mesh::Draw(Renderer& renderer, Shader& shader) const 
{
    unsigned int diffuseN = 0;
    unsigned int specularN = 0;
    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        std::string texType = m_Textures[i].Type;
        std::string number;
        if (texType == "texture_diffuse")
            number = std::to_string(diffuseN++);
        else if (texType == "texture_specular")
            number = std::to_string(specularN++);

        m_Textures[i].texture->Bind(i);
        shader.SetUniform1i(("u_Material." + texType + number).c_str(), i);
    }
    
    renderer.Draw(*m_VAO, *m_IBO, shader);
}

/***************************************************************/

/*-------------------------------------------------------------*/
/*                        Model                                */
/*-------------------------------------------------------------*/
Model::Model(const std::string& path)
    : m_FilePath(path)
{
    m_Directory = path.substr(0, path.find_last_of('/'));

    loadModel();
}

Model::~Model()
{

}

void Model::Draw(Renderer& renderer, Shader& shader) const
{
    for (int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i].Draw(renderer, shader);
    }
}

void Model::loadModel()
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(m_FilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace); 

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl; 
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<VertexInfo> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureInfo> textures;

    // get vertex 
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        VertexInfo vi;
        vi.Position  = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vi.Normal    = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0])
            vi.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        else
            vi.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vi);
    }

    // get index
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh->mFaces[i].mIndices[j]);
    }

    // get texture
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<TextureInfo> v_diffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<TextureInfo> v_specular = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

        textures.insert(textures.end(), v_diffuse.begin(), v_diffuse.end());
        textures.insert(textures.end(), v_specular.begin(), v_specular.end());
    }
    return Mesh(vertices, indices, textures);
}

std::vector<TextureInfo> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
    std::vector<TextureInfo> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString tpath;
        material->GetTexture(type, i, &tpath);
        std::cout << tpath.C_Str() << std::endl;

        if (m_TextureInfoCache.find(tpath.C_Str()) == m_TextureInfoCache.end())
        {
            std::string fullpath;
            fullpath = m_Directory + "/" +tpath.C_Str();
            m_TextureInfoCache[tpath.C_Str()] = { std::make_shared<Texture>(fullpath), typeName };
        }
        
        textures.push_back(m_TextureInfoCache[tpath.C_Str()]);
    }
    return textures;    
}

