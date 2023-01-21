#include"Vbo.h"
#include"Renderer.h"


Vbo::Vbo(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererId);
    //select the buffer that we are going to work on it
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    //add data to the buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vbo::~Vbo()
{
    glDeleteBuffers(1, &m_RendererId);
}

void Vbo::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}

void Vbo::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
