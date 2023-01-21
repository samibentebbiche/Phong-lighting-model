#pragma once
#include"Vbo.h"
#include"VertexBufferLayout.h"

class Vao
{
private:
    unsigned int m_RendererID;
public:
    Vao();
    ~Vao();
    void addBuffer(const Vbo& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;
};
