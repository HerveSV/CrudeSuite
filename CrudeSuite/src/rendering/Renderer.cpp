//
//  Renderer.cpp
//  CrudeEngine
//
//  Created by Hervé Schmit-Veiler on 4/27/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "Renderer.hpp"

#include <GLFW/glfw3.h>

/**
 Crude::
 **/


bool Crude::windowShouldClose(Window *window)
{
    return glfwWindowShouldClose(window);
}

void Crude::closeWindow(Window *window)
{
    return glfwSetWindowShouldClose(window, true);
}

void Crude::destroyWindow(Window *window)
{
    glfwDestroyWindow(window);
}

unsigned int Crude::getKey(Window *window, unsigned int key)
{
    return glfwGetKey(window, key);
}

void Crude::initOpenGL(unsigned int CONTEXT_VERSION_MAJOR = 3,
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

void Crude::terminateOpenGL()
{
    glfwTerminate();
}


bool Crude::initGLLoader()
{
    bool err;
    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    
    assert(!err && "Fatal Error: Failed to initialise OpenGL loader!");
    
    return err;
}



/**
 Crude::Renderer::
 **/


/*Crude::Renderer::Renderer()
{
    
}

Crude::Renderer::~Renderer()
{
    glfwTerminate();
}*/



Crude::Window* Crude::Renderer::createWindow(int width, int height,
                                             std::string name)
{
    assert((width >= 0 || height >= 0) && "You can't have negative window width or length!");
    
    m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    m_windowWidth = width;
    m_windowHeight = height;
    
    if(m_window == NULL)
    {
        std::cout << "Failed to create GLFW window with name: " << name << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(m_window);
    return m_window;
    
}

void Crude::Renderer::destroyWindow()
{
    Crude::destroyWindow(m_window);
}

void Crude::Renderer::setWindow(Crude::Window* window)
{
    if(window == nullptr)
    {
        std::cout << "Warning: This window does not exist!" <<std::endl;
    }
    if(m_window != nullptr)
    {
        std::cout << "Window currently in existance will be overrided!" <<std::endl;
    }
    glfwMakeContextCurrent(window);
    m_window = window;
}

Crude::Window* Crude::Renderer::getWindow()
{
    return m_window;
}

bool Crude::Renderer::windowShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

bool Crude::Renderer::checkWindow()
{
    if(m_window == NULL)
    {
        std::cout<<"Window currently inactive!"<<std::endl;
        return false;
    }
    return true;
}

void Crude::Renderer::enableVsync(bool enable)
{
    glfwSwapInterval(enable);
}

void Crude::Renderer::enablePolygonMode(bool enable)
{
    if(enable)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Crude::Renderer::setClearColour(float r, float g, float b, float a)
{
    m_windowClearColour = glm::vec4(r, g, b, a);
    glClearColor(r, g, b, a);
}

void Crude::Renderer::clearColourBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


void Crude::Renderer::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void Crude::Renderer::clearDeptBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Crude::Renderer::endFrame()
{
    swapBuffers();
    pollEvents();
}

void Crude::Renderer::pollEvents()
{
    glfwPollEvents();
}

void Crude::Renderer::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Crude::Renderer::draw(VertexArray &vao, IndexBuffer &ebo, Shader &shader)
{
    shader.bind();
    vao.bind();
    ebo.bind();
    glDrawElements(GL_TRIANGLES, ebo.getCount(), GL_UNSIGNED_INT, 0);
}

void Crude::Renderer::draw(VertexArray &vao, unsigned int verticesCount, Shader &shader)
{
    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void Crude::Renderer::draw(const unsigned int &vao, unsigned int verticesCount, Shader &shader)
{
    shader.bind();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}






/**
 ImGui::
 **/



void ImGui::CrudeInit(GLFWwindow *window, bool darkMode)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    if(darkMode)
    {
        ImGui::StyleColorsDark();
    }
    else
    {
        ImGui::StyleColorsClassic();
    }
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    std::string glsl_version;
#if __APPLE__
    // GL 3.2 + GLSL 150
    glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    glsl_version = "#version 130";
#endif

    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void ImGui::CrudeNewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGui::CrudeRenderFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGui::CrudeTerminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
