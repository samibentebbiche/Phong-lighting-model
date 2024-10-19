#include"Renderer.h"
#include<iostream>

void Renderer::Clear()const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Vao& va, const Ibo& ib, const Shader& shader)const
{
    shader.Bind();
    ib.Bind();     
    va.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
    
}