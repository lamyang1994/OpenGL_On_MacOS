#shader vertex 
#version 330 core

layout (location = 0) in vec3 position;
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
   gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0f);
   v_Normal = u_NormalMatrix * Normal;
   v_ObjPos = vec3(u_Model * vec4(position, 1.0f));
   v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec3 v_Normal;
in vec3 v_ObjPos;
in vec2 v_TexCoord;

layout (location = 0) out vec4 color;

struct Material {
    sampler2D diffuse; 
    sampler2D specular; 
    float shininess;
};

struct DirLight {
    vec3 lightDirection;
    vec3 lightColor;
};

struct SpotLight {
    vec3 lightPosition;
    vec3 lightColor;

    float constant;
    float linear;
    float quadratic;

    vec3 spotDir;
    float cutOff;
    float outerCutOff;
};

struct PointLight {
    vec3 lightPosition;
    vec3 lightColor;

    float constant;
    float linear;
    float quadratic;
};
#define NUM_POINT_LIGHTS 4

uniform Material u_Material;
uniform DirLight u_DirLight;
uniform SpotLight u_SpotLight;
uniform PointLight u_PointLights[NUM_POINT_LIGHTS];

uniform vec3 u_CameraPos;
uniform bool u_isDirLight;
uniform bool u_isSpotLight;
uniform int  u_numPointLight;

vec3 calDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calSpotLight(SpotLight light, vec3 normal, vec3 viewDir);
vec3 calPointLight(PointLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 OutputColor;
    vec3 viewDir = normalize(v_ObjPos - u_CameraPos);
    vec3 norm = normalize(v_Normal);

    if (u_isDirLight)
        OutputColor += calDirLight(u_DirLight, norm, viewDir);
    if (u_isSpotLight)
        OutputColor += calSpotLight(u_SpotLight, norm, viewDir);
    for (int i = 0; i < u_numPointLight; i++)
    {
        OutputColor += calPointLight(u_PointLights[i], norm, viewDir);
    }

    color = vec4(OutputColor, 1.0f);

}

vec3 calDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 vecTexture = vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 normDir = normalize(light.lightDirection);
    // ambient
    vec3 ambient = (0.05 * light.lightColor) * vecTexture;

    // diffuse
    float diff = max(dot(-normDir, normal), 0.0f);
    vec3 diffuse = (0.5 * light.lightColor) * diff * vecTexture;

    // specular
    vec3 reflectDir = reflect(normDir, normal);
    float spec = pow(max(dot(reflectDir, -viewDir), 0.0f), u_Material.shininess);
    vec3 specular = light.lightColor * spec * vec3(texture(u_Material.specular, v_TexCoord));

    return (ambient + diffuse + specular);
}

vec3 calSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(v_ObjPos - light.lightPosition);
    float distance = length(light.lightPosition - v_ObjPos);
    float attenuation = 1.0f / (light.constant + (light.linear * distance) + (light.quadratic * distance * distance)); 

    //Spotlight or Normal
    float theta = dot(lightDir, normalize(light.spotDir));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    // ambient
    // vec3 ambient = (0.2 * light.lightColor) * vecTexture;

    // diffuse
    float diff = max(dot(-lightDir, normal), 0.0f);
    vec3 diffuse = light.lightColor * diff * vec3(texture(u_Material.diffuse, v_TexCoord));

    // specular
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(reflectDir, -viewDir), 0.0f), u_Material.shininess);
    vec3 specular = light.lightColor * spec * vec3(texture(u_Material.specular, v_TexCoord));

    return attenuation * intensity * (diffuse + specular);

}

vec3 calPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(v_ObjPos - light.lightPosition);
    float distance = length(light.lightPosition - v_ObjPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * distance * distance)); 

    vec3 vecTexture = vec3(texture(u_Material.diffuse, v_TexCoord));

    // ambient
    vec3 ambient = (0.05 * light.lightColor) * vecTexture;

    // diffuse
    float diff = max(dot(-lightDir, normal), 0.0f);
    vec3 diffuse = (0.5 * light.lightColor) * diff * vecTexture;

    // specular
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(reflectDir, -viewDir), 0.0f), u_Material.shininess);
    vec3 specular = light.lightColor * spec * vec3(texture(u_Material.specular, v_TexCoord));

    return attenuation * (ambient + diffuse + specular);
}