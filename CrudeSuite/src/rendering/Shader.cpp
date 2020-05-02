//
//  Shader.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "Shader.hpp"

#include <GL/glew.h> 
#include <GLFW/glfw3.h>



Crude::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Crude::Shader::Shader(const char* vertexFragmentPath)
{
    //implement parser to parse single file into two shader source codes
}

void Crude::Shader::bind() const
{
    glUseProgram(m_ID);
}

void Crude::Shader::unbind() const
{
    glUseProgram(0);
}

int Crude::Shader::getUniformLocation(const std::string &name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    {
        return m_uniformLocationCache[name];
    }
    
    int location = glGetUniformLocation(m_ID, name.c_str());
    if(location == -1)
    {
        std::cout<<"Warning: uniform "<<name<<" does not exist!"<<std::endl;
    }
    m_uniformLocationCache[name] = location;
    return location;
}

void Crude::Shader::setBool(const std::string &name, bool value, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform1i(getUniformLocation(name), (int)value);
        unbind();
    }
    else
    {
        glUniform1i(getUniformLocation(name), (int)value);
    }
    
}

void Crude::Shader::setInt(const std::string &name, int value, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform1i(getUniformLocation(name), value);
        unbind();
    }
    else
    {
        glUniform1i(getUniformLocation(name), value);
    }
}

void Crude::Shader::setFloat(const std::string &name, float value, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform1f(getUniformLocation(name), value);
        unbind();
    }
    else
    {
        glUniform1f(getUniformLocation(name), value);
    }
   
}

void Crude::Shader::setVec2f(const std::string &name, float x, float y, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform2f(getUniformLocation(name), x, y);
        unbind();
    }
    else
    {
        glUniform2f(getUniformLocation(name), x, y);
    }
}

void Crude::Shader::setVec3f(const std::string &name, float x, float y, float z, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform3f(getUniformLocation(name), x, y, z);
        unbind();
    }
    else
    {
        glUniform3f(getUniformLocation(name), x, y, z);
    }
}

void Crude::Shader::setVec4f(const std::string &name, float x, float y, float z, float w, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniform4f(getUniformLocation(name), x, y, z, w);
        unbind();
    }
    else
    {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }
}

void Crude::Shader::setMat4(const std::string &name, const glm::mat4 &mat, bool bindOrNot)
{
    if(bindOrNot)
    {
        bind();
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
        unbind();
    }
    else
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void Crude::Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
