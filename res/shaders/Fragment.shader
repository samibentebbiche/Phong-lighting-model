#version 330 core

out vec4 color;

uniform vec4 u_Color;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
   float specularStrength = 0.3f;
   //calculating diffuse color
   vec3 norm = normalize(vec3(Normal));
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = max(dot(norm, lightDir),0.0f);
   vec4 diffuse = vec4(diff * vec3(lightColor), 1.0f);

   // calculating ambiante color
   float ambiantStrength = 0.1f;
   vec4 ambiant = ambiantStrength * lightColor;


   //specular 
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256.0);
   vec4 specular = specularStrength * spec * lightColor;
   // calculating the resulting color
   //color = vec4(spec,spec,spec,0.1f);
   //color = specular;
   color = (ambiant + diffuse + specular) * u_Color;

};