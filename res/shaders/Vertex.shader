#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;


void main()
{
  TexCoords = aTexCoords;
  
   Normal = mat3(transpose(inverse(u_Model)))* aNormal; // This simplifies for debugging purposes
   //Normal = aNormal;
   FragPos = vec3(u_Model * position);
   gl_Position = u_MVP * position;
};
