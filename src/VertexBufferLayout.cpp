#include"VertexBufferLayout.h"


void VertexBufferLayout::Push(unsigned int count,unsigned int elemType)
{
    switch(elemType)
    {
        case GL_FLOAT:

            m_Elements.push_back( { GL_FLOAT, count, GL_FALSE });
            m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
            break;



        case GL_UNSIGNED_INT:

            m_Elements.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
            m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);

            break;



        case GL_UNSIGNED_BYTE:

            m_Elements.push_back( { GL_UNSIGNED_BYTE, count, GL_TRUE } );
            m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
            break;

    }

}