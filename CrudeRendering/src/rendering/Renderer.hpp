//
//  Renderer.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <iostream>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"


class Renderer
{
private:
    //const std::string glsl_version = "#version 330";
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    glm::vec4 m_windowClearColour;
    
    bool checkWindow();
public:
    Renderer();
    ~Renderer();
    
    void initOpenGL(unsigned int CONTEXT_VERSION_MAJOR,
                    unsigned int CONTEXT_VERSION_MINOR,
                    unsigned int OPENGL_PROFILE,
                    unsigned int FORWARD_COMPAT);
    
    
    
    void setClearColour(float r, float g, float b, float a);
    
    void clearColourBuffer() const;
    
    void enableDepthTest() const;
    
    void clearDeptBuffer() const;
    
    void draw(VertexArray &vao, IndexBuffer &ebo, Shader &shader) const;
    
    void draw(VertexArray &vao, unsigned int verticesCount, Shader &shader) const;
    
  
};

#endif /* Renderer_hpp */
