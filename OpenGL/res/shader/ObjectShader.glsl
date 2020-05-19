#shader vertex 
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 Normal;

flat out vec3 v_Normal;
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

flat in vec3 v_Normal;
in vec3 v_ObjPos;

layout (location = 0) out vec4 color;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;
}; 

uniform vec3 u_CameraPos;
uniform Light u_Light;
uniform Material u_Material;

void main()
{
    // ambient
    vec3 ambient = u_Material.ambient * u_Light.ambient;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.position - v_ObjPos);
    float diff = max(dot(lightDir, norm), 0.0f);
    vec3 diffuse = (diff * u_Material.diffuse) * u_Light.diffuse;

    // specular
    vec3 viewDir = normalize(u_CameraPos - v_ObjPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specValue = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);
    vec3 specular = (u_Material.specular * specValue) * u_Light.diffuse;
    
    color = vec4((ambient + diffuse + specular), 1.0f);
}