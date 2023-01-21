#pragma once
#include"vector"
#include<GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        default:
            return 0;
        }
        
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        : m_Stride(0){}
    void Push(unsigned int count,unsigned int type);

    inline const std::vector<VertexBufferElement> GetElement()const& {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}
    
};