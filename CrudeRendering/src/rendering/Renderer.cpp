//
//  Renderer.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "Renderer.hpp"

#include <GLFW/glfw3.h>

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    glfwTerminate();
}

void Renderer::initOpenGL(unsigned int CONTEXT_VERSION_MAJOR = 3,
                          unsigned int CONTEXT_VERSION_MINOR = 3,
                          unsigned int OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE,
                          unsigned int FORWARD_COMPAT = GL_TRUE)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, FORWARD_COMPAT);
}

/*bool Renderer::createWindow(unsigned int width, unsigned int height,
                            std::string name)
{
    m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    
    if(m_window == NULL)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return false;
    }
    return true;
}

bool Renderer::checkWindow()
{
    if(m_window == NULL)
    {
        std::cout<<"Window currently inactive!"<<std::endl;
        return false;
    }
    return true;
}*/

void Renderer::enableDepthTest() const
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::clearDeptBuffer() const
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(VertexArray &vao, IndexBuffer &ebo, Shader &shader) const
{
    shader.bind();
    vao.bind();
    ebo.bind();
    glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::draw(VertexArray &vao, unsigned int verticesCount, Shader &shader) const
{
    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void Renderer::setClearColour(float r, float g, float b, float a)
{
    m_windowClearColour = glm::vec4(r, g, b, a);
    glClearColor(r, g, b, a);
}

void Renderer::clearColourBuffer() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    }
