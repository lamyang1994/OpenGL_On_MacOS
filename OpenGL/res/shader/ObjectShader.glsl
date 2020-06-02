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

struct Light {
    vec4 lightVector;
    vec3 lightColor;

    vec3 spotDir;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

struct Material {
    // sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

uniform vec3 u_CameraPos;
uniform Light u_Light;
uniform Material u_Material;
uniform bool u_FlashLight;

void main()
{
    vec3 lightDir;
    float attenuation = 1.0f;

    // Point-Light or Parallel-Light 
    if (u_Light.lightVector.w == 1.0)
    {
        lightDir = normalize(u_Light.lightVector.xyz - v_ObjPos);
        float distance = length(u_Light.lightVector.xyz - v_ObjPos);
        attenuation = 1.0 / (u_Light.constant + u_Light.linear*distance + u_Light.quadratic*distance*distance);
    }
    else
    {
        lightDir = normalize(-u_Light.lightVector.xyz);
    }

    //Spotlight or Normal
    float theta = dot(lightDir, normalize(-u_Light.spotDir));
    float epsilon = u_Light.cutOff - u_Light.outerCutOff;
    float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0f, 1.0f);

    // ambient
    vec3 ambient = vec3(texture(u_Material.diffuse, v_TexCoord)) * (0.2 * u_Light.lightColor);

    // diffuse
    vec3 norm = normalize(v_Normal);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = (diff * vec3(texture(u_Material.diffuse, v_TexCoord))) * (0.5 * u_Light.lightColor);

    // specular
    vec3 viewDir = normalize(u_CameraPos - v_ObjPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);
    vec3 specular = (vec3(texture(u_Material.specular, v_TexCoord)) * specValue) * u_Light.lightColor;

    if (u_FlashLight)
    {
        diffuse *= intensity;
        specular *= intensity;
    }
    color = vec4(attenuation * (ambient + diffuse + specular), 1.0f);
}