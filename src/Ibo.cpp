#include"Ibo.h"
#include"Renderer.h"


Ibo::Ibo(const unsigned int* data, unsigned int count)
:m_Count(count)
{
    glGenBuffers(1, &m_RendererId);
    //select the buffer that we are going to work on it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    //add data to the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(unsigned int), data, GL_STATIC_DRAW);
}

Ibo::~Ibo()
{
    glDeleteBuffers(1, &m_RendererId);
}

void Ibo::Bind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}

void Ibo::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

