/*// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
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
#endif*/

// Include glfw3.h after our OpenGL definitions
#include "CrudeSuite.h"

using namespace Crude;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


void processInput(Crude::Window *window)
{
    if(Crude::getKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Crude::closeWindow(window);
}

int main()
{
    //std::string glsl_version = "#version 330";
    const int windowWidth = 1280;
    const int windowHeight = 800;
    
    Crude::initOpenGL(3, 3, GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    Crude::Window* window = Renderer::createWindow(windowWidth, windowHeight);
    if (window == NULL)
        return 1;
    
    Renderer::enableVsync(true); // Enable vsync
    
    Crude::initGLLoader();
    ImGui::CrudeInit(window, true);
    
    Crude::Shader shaderProgram("res/shaderSources/standardShader.vs", "res/shaderSources/standardShader.fs");
    shaderProgram.setInt("uTexture1", 0);
    shaderProgram.setInt("uTexture2", 1);
    shaderProgram.setInt("uTexture3", 2);
    
    float vertices3[]
    {
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f, //top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,//bottom right
        -0.5, -0.5f, 0.0f,      0.0f, 0.0f,//bottom left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,//top left
    };
    
    unsigned int indices3[]
    {
        1, 0, 3, //front face
        1, 2, 3,
    };
    
    float vertices[]
    {
        //positions             //texure
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f, //top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,//bottom right
        -0.5, -0.5f, 0.0f,      0.0f, 0.0f,//bottom left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,//top left
        
        0.5f, 0.5f, -0.5f,      1.0f, 1.0f,//top right
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,//bottom right
        -0.5, -0.5f, -0.5f,     0.0f, 0.0f,//bottom left
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,//top left
        
    };
    
    unsigned int indices[]
    {
        1, 0, 3, //front face
        1, 2, 3,
        
        0, 4, 7, //top face
        0, 3, 7,
        
        5, 4, 7, //back face
        5, 6, 7,
        
        1, 5, 6, //bottom face
        1, 2, 6,
        
        5, 4, 0, //right face - positive x
        5, 1, 0,
        
        3, 7, 6, //left face - negative x
        3, 2, 6,
        
    };
    
    float vertices2[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    
    
    Crude::VertexArray vao2;
    Crude::VertexBuffer vbo2(vertices2, sizeof(vertices2));
    Crude::VertexBufferLayout layout2;

    layout2.push<float>(3);
    layout2.push<float>(2);
    vao2.addVertexBuffer(vbo2, layout2);
    
    Crude::VertexArray vao;
    Crude::VertexBuffer vbo(vertices, sizeof(vertices));
    Crude::VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    Crude::IndexBuffer ebo(indices, 36);
    vao.addVertexBuffer(vbo, layout);
    vao.addIndexBuffer(ebo);
    
    Crude::VertexArray vao3;
    Crude::VertexBuffer vbo3(vertices3, sizeof(vertices3));
    Crude::VertexBufferLayout layout3;
    layout3.push<float>(3);
    layout3.push<float>(2);
    
    Crude::IndexBuffer ebo3(indices3, 6);
    vao3.addVertexBuffer(vbo3, layout3);
    vao3.addIndexBuffer(ebo3);
    
    Crude::Texture texture1("res/textures/container.jpg", GL_RGB, true);
    Crude::Texture texture2("res/textures/awesomeface.png", GL_RGBA, true);
    Texture logoTexture("res/textures/CrudeLogoBackground.png", GL_RGBA, true);
    
    
    Crude::Camera cam(Camera_type::PERSPECTIVE, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    
    view = cam.getViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    shaderProgram.bind();

    shaderProgram.setFloat("uVisibility1", 1.0f);
    shaderProgram.setFloat("uVisibility3", 0.0f); //get multiple textures working
    shaderProgram.setFloat("uVisibility2", 0.0f);
    texture1.bind(0);
    logoTexture.bind(1);
    texture2.bind(2);
    
    glm::vec3 rotation(45.0f, 45.0f, 45.0f);
    glm::vec4 clearColour = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    Renderer::enableDepthTest();
    while(!Renderer::windowShouldClose())
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
         model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        Renderer::setClearColour(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
        processInput(window);
        Renderer::clearColourBuffer();
        Renderer::clearDeptBuffer();

        Renderer::enablePolygonMode(false);
        shaderProgram.bind();

        shaderProgram.setMat4("uMVP", projection*view*model);

        Renderer::draw(vao2, 36, shaderProgram);
        
        ImGui::CrudeNewFrame();
        
        ImGui::ShowDemoWindow();
        ImGui::Begin("Hey");
        ImGui::ColorEdit3("clear color", (float*)&clearColour);
        ImGui::SliderFloat("X Rotation", &rotation.x, 0, 360);
        ImGui::SliderFloat("Y Rotation", &rotation.y, 0, 360);
        ImGui::SliderFloat("Z Rotation", &rotation.z, 0, 360);
        ImGui::End();
        
        ImGui::CrudeRenderFrame();
        
        Renderer::endFrame();
    }
    
    ImGui::CrudeTerminate();
    Renderer::destroyWindow();
    Crude::terminateOpenGL();

    return 0;
}
