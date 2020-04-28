//
//  Shader.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/26/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    unsigned int m_ID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    
    Shader(const char* vertexFragmentPath);
    // activate the shader
    // ------------------------------------------------------------------------
    void bind() const;
    
    void unbind() const;
    // utility uniform functions
    // ------------------------------------------------------------------------
    int getUniformLocation(const std::string &name);
    
    void setBool(const std::string &name, bool value);
 
    void setInt(const std::string &name, int value);
    
    void setFloat(const std::string &name, float value);
    
    void setVec2f(const std::string &name, float x, float y);
    
    void setVec3f(const std::string &name, float x, float y, float z);
    
    void setVec4f(const std::string &name, float x, float y, float z, float w);
    
    void setMat4(const std::string &name, const glm::mat4 &mat);
    
    unsigned int getID() const {return m_ID;}
    
private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
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
};


#endif /* Shader_hpp */
