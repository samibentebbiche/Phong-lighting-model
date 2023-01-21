#pragma once


class Vbo
{
private:

    unsigned int m_RendererId;

public:

    Vbo(const void* data, unsigned int size);
    ~Vbo();

    void Bind() const;
    void Unbind() const;
};