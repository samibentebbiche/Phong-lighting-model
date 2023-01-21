#pragma once
#include<string>
#include<unordered_map>

class Shader
{
private:
    std::string m_VertFilePath;
    std::string m_FragFilePath;
    unsigned int m_RendererID;
    // caching system for uniforms
    std::unordered_map<std::string,int> m_UniformLocationCache;
public:
    Shader(const char* vert_filepath, const char* frag_filepath);
    ~Shader();

    void Bind()const;
    void Unbind()const;

    //set uniform
    void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
    void SetUniform1f(const std::string& name,float v);
    void SetUniform1i(const std::string& name,int v);
private:
    std::string get_file_contents(const char* filename);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int GetUniformLocation(const std::string& name);
};

