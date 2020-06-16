#shader vertex 
#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 texCoord;

out vec3 v_Normal;
out vec3 v_ObjPos;
out vec2 v_TexCoord;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(Position, 1.0f);
    v_Normal = u_NormalMatrix * Normal;
    v_ObjPos = vec3(u_Model * vec4(Position, 1.0f));
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec3 v_Normal;
in vec3 v_ObjPos;
in vec2 v_TexCoord;

layout (location = 0) out vec4 color;

struct Material {
    sampler2D texture_diffuse0; 
    sampler2D texture_diffuse1; 
    sampler2D texture_diffuse2; 
    sampler2D texture_specular0; 
    sampler2D texture_specular1; 
    sampler2D texture_specular2; 
    float shininess;
};

struct DirLight {
    vec3 lightDirection;
    vec3 lightColor;
};

uniform Material u_Material;
uniform DirLight u_DirLight;
uniform vec3 u_CameraPos;

vec3 calDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 OutputColor;
    vec3 viewDir = normalize(v_ObjPos - u_CameraPos);
    vec3 norm = normalize(v_Normal);

    OutputColor += calDirLight(u_DirLight, norm, viewDir);
    // OutputColor = vec3(texture(u_Material.texture_diffuse0, v_TexCoord));
    color = vec4(OutputColor, 1.0f);
}

vec3 calDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 vecTexture = vec3(texture(u_Material.texture_diffuse0, v_TexCoord));
    vec3 normDir = normalize(light.lightDirection);
    // ambient
    vec3 ambient = (0.1 * light.lightColor) * vecTexture;

    // diffuse
    float diff = max(dot(-normDir, normal), 0.0f);
    vec3 diffuse = (0.8 * light.lightColor) * diff * vecTexture;

    // specular
    vec3 reflectDir = reflect(normDir, normal);
    float spec = pow(max(dot(reflectDir, -viewDir), 0.0f), u_Material.shininess);
    vec3 specular = light.lightColor * spec * vec3(texture(u_Material.texture_specular0, v_TexCoord));

    return (ambient + diffuse + specular);
}