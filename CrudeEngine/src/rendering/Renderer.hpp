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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"


class Renderer
{
private:
    GLFWwindow* m_window = NULL;
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
    
    bool createWindow(unsigned int width, unsigned int height,
                      std::string name);
    
    void setClearColour(float r, float g, float b, float a)
    {
        m_windowClearColour = glm::vec4(r, g, b, a);
        glClearColor(r, g, b, a);
    }
    
    void clearColourBuffer() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void enableDepthTest() const;
    
    void clearDeptBuffer() const;
    
    void draw(VertexArray &vao, IndexBuffer &ebo, Shader &shader) const;
    
    void draw(VertexArray &vao, unsigned int verticesCount, Shader &shader) const;
    
    void closeWindow()
    {
        glfwSetWindowShouldClose(m_window, true);
    }
    
    
    bool windowShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }
    
    void outputFrame()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    
    GLFWwindow* getWindow() const {return m_window;}
};

#endif /* Renderer_hpp */
