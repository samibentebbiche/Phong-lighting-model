#pragma once

#include<GL/glew.h>

#include"Vao.h"
#include"Ibo.h"
#include"Shader.h"


class Renderer
{
private:
    /* data */
public:
    void Clear()const;
    void Draw(const Vao& va, const Ibo& ib, const Shader& shader) const;
};
