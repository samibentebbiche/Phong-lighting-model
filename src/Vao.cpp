#include"Vao.h"
#include"Renderer.h"
#include"VertexBufferLayout.h"

Vao::Vao()
{
    glGenVertexArrays(1,&m_RendererID);
    
}
Vao::~Vao()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
void Vao::addBuffer(const Vbo& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind(); 
    const auto& elements = layout.GetElement();
    unsigned int offset = 0;
    for(unsigned int i = 0;i<elements.size();i++)
    {
        const auto& element = elements[i];
        glVertexAttribPointer(i ,element.count,element.type, element.normalized , layout.GetStride(), (const void*) offset);
        glEnableVertexAttribArray(i);

        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void Vao::Bind() const
{
    glBindVertexArray(m_RendererID);
}
void Vao::Unbind() const
{
    glBindVertexArray(0);
}