#include"Shader.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include"Renderer.h"


Shader::Shader(const char* vert_filepath, const char* frag_filepath)
    :m_VertFilePath(vert_filepath), m_FragFilePath(frag_filepath),m_RendererID(0)
{   
    m_VertFilePath = get_file_contents(vert_filepath);
    //std::string vertexShader = m_VertFilePath;
    m_FragFilePath = get_file_contents(frag_filepath);
    //std::string fragmentShader = m_FragFilePath;
    m_RendererID = CreateShader(m_VertFilePath, m_FragFilePath);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

// Reads a text file and outputs a string with everything in the text file
std::string Shader::get_file_contents(const char* filename)
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


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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



void Shader::Bind()const
{
    glUseProgram(m_RendererID);
}
void Shader::Unbind()const
{
    glUseProgram(0);
}
void Shader::SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::SetUniform3f(const std::string& name,float v0,float v1,float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}


void Shader::SetUniform1f(const std::string& name,float v)
{
    glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUniformMat4f(const std::string& name,const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1i(const std::string& name,int v)
{
    glUniform1i(GetUniformLocation(name), v);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location =  glGetUniformLocation(m_RendererID, name.c_str());
    if(location == -1 )
        std::cout<<"Warning: Uniform "<<name << "doesn't exist! "<<std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}