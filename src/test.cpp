
#define GLEW_STATIC

#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>

#include"Renderer.h"
#include"Vbo.h"
#include"Ibo.h"
#include"Vao.h"


// Reads a text file and outputs a string with everything in the text file
static std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Error handling
    
    /*int result,
    glGetShaderiv(id, GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE)
    {
       int lenght;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&lenght);
        char* message = (char*)alloca(lenght * sizeof(char)); 
        glGetShaderInfoLog(id,lenght,&lenght,message);
        std::cout<< "Failed to Compile "<<
            (type==GL_VERTEX_SHADER ? "vertex":"fragment")
            << "Shader!"<<std::endl;
        std::cout<< message << std::endl;

        glDeleteShader(id);
        return 0;
    }*/
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

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

    std::string vertexShader = get_file_contents("../res/shaders/Vertex.shader");
    std::string fragmentShader = get_file_contents("../res/shaders/Fragment.shader");
    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);

    int location =  glGetUniformLocation(shader, "u_Color");
    //ASSERT(location != -1);
    glUniform4f(location,0.8f, 0.3f, 0.8f, 1.0f);
    /* Loop until the user closes the window */
    
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    glUseProgram(0);

    float r = 0.0f;
    float inc = 0.01f;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(location, r , 0.3f, 0.8f, 1.0f);
        
        ib.Bind();     
        va.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
    glDeleteProgram(shader);
    return 0;
}