#version 330 core

struct Material {
    //vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;
in vec2 TexCoords;

struct Light {

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
out vec4 color;

uniform vec4 u_Color;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
   //calculating diffuse color
   vec3 norm = normalize(vec3(Normal));
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir),0.0f);
   vec4 diffuse = vec4(1.0f) * vec4(light.diffuse * diff * vec3(texture(material.diffuse, TexCoords))  , 1.0f);

   // calculating ambiante color
   vec4 ambiant = vec4(1.0f) * vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)),1.0f) ;


   //specular
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

   vec4 specular = vec4(1.0f) * vec4(light.specular * spec * vec3(texture(material.specular, TexCoords)),1.0f);

   // calculating the resulting colorz
  color = (ambiant + diffuse + specular) * u_Color;

};
