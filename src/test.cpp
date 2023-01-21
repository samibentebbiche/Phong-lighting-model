
#define GLEW_STATIC

#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include"Renderer.h"
#include"Vbo.h"
#include"Ibo.h"
#include"Vao.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include<iostream>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if(glewInit()!=GLEW_OK)
        std::cout<<"ERROR !"<<std::endl;
 
    
    float positions [] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f, 0.5f, //2
        -0.5f, 0.5f //3
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //Vbo;
    Vbo vb = Vbo(positions,4 * 2 * sizeof(float));


    //vao
    Vao va;
    VertexBufferLayout layout;
    layout.Push(2, GL_FLOAT);
    
    va.addBuffer(vb, layout);
    
    
    

    Ibo ib = Ibo(indices, 6);


    Shader shader("../res/shaders/Vertex.shader","../res/shaders/Fragment.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color",0.8f, 0.3f, 0.8f, 1.0f);
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.0f;
    float inc = 0.01f;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r , 0.3f, 0.8f, 1.0f);
        renderer.Draw(va,ib,shader);
        //glDrawArrays(GL_TRIANGLES,0,6);

        if(r > 1.0f)
            inc = -0.01f;
        else if(r<0.0f)
            inc = 0.01f;

        r += inc;
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}