//
//  Renderer.hpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

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

// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace Crude
{
    typedef GLFWwindow Window;
    
    bool windowShouldClose(Window* window);
    
    void closeWindow(Window* window); //not to be confused with destroyWindow(Window*);
    
    void destroyWindow(Window* window);
    
    unsigned int getKey(Window* window, unsigned int key);
    
    void initOpenGL(unsigned int CONTEXT_VERSION_MAJOR,
                    unsigned int CONTEXT_VERSION_MINOR,
                    unsigned int OPENGL_PROFILE,
                    unsigned int FORWARD_COMPAT);
    
    void terminateOpenGL();
    
    bool initGLLoader();
    
    
    
    class Renderer
    {
    private:
        //const std::string glsl_version = "#version 330";
        inline static Window* m_window;
        
        inline static unsigned int m_windowWidth;
        
        inline static unsigned int m_windowHeight;
        
        inline static glm::vec4 m_windowClearColour;
        
        
    public:
        
        static Window* createWindow(int width, int height, std::string name = "cookie&dummy");
        
        static void destroyWindow();
        
        static void setWindow(Window* window);
        
        static Window* getWindow();
        
        static bool windowShouldClose();
        
        static bool checkWindow();

        static void enableVsync(bool enable);
        
        static void enablePolygonMode(bool enable);
        
        static void setClearColour(float r, float g, float b, float a);
        
        static void clearColourBuffer();
        
        static void enableDepthTest();
        
        static void clearDeptBuffer();
        
        static void pollEvents();
        
        static void swapBuffers();
        
        static void endFrame();
        
        static void draw(VertexArray &vao, IndexBuffer &ebo, Shader &shader);
        
        static void draw(VertexArray &vao, unsigned int verticesCount, Shader &shader);
        
        static void draw(const unsigned int &vao, unsigned int verticesCount, Shader &shader);
        
        
    };

}

namespace ImGui
{
    void CrudeInit(Crude::Window* window, bool darkMode = false);
    
    void CrudeNewFrame();
    
    void CrudeRenderFrame();
    
    void CrudeTerminate();
}

#endif /* Renderer_hpp */
