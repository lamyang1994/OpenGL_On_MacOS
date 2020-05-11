#shader vertex 
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Normal;

out vec3 v_Normal;
out vec3 v_ObjPos;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

void main()
{
   gl_Position = u_Proj * u_View * u_Model * vec4(position, 1.0f);
   v_Normal = u_NormalMatrix * Normal;
   v_ObjPos = vec3(u_Model * vec4(position, 1.0f));
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec3 v_Normal;
in vec3 v_ObjPos;

uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    // diffuce
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_LightPos - v_ObjPos);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuce = diff * u_LightColor;

    // specular
    float specularStrenth = 0.5f;
    vec3 viewDir = normalize(u_CameraPos - v_ObjPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrenth * specValue * u_LightColor;
    
    color = vec4((ambient + diffuce + specular) * u_ObjectColor, 1.0f);
}