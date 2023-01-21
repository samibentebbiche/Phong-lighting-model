#pragma once


class Ibo
{
private:

    unsigned int m_RendererId;
    unsigned int m_Count;

public:

    Ibo(const unsigned int* data, unsigned int count);
    ~Ibo();

    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const { return m_Count;}
};