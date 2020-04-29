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

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/Shader.hpp"
#include "rendering/IndexBuffer.hpp"
#include "rendering/VertexBuffer.hpp"
#include "rendering/VertexBufferLayout.hpp"
#include "rendering/VertexArray.hpp"
#include "rendering/Texture.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int main()
{
    const char* glsl_version = "#version 150";
    const size_t windowWidth = 760;
    const size_t windowHeight = 500;
    Renderer renderer;
    renderer.initOpenGL(3, 3, GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "cookie&dummy", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    
    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    Shader shaderProgram("res/shader_sources/standardShader.vs", "res/shader_sources/standardShader.fs");
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
    
    
    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    
    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    IndexBuffer ebo(indices, 36);
    vao.addVertexBuffer(vbo, layout);
    vao.addIndexBuffer(ebo);
    
    VertexArray vao3;
    VertexBuffer vbo3(vertices3, sizeof(vertices3));
    VertexBufferLayout layout3;
    layout3.push<float>(3);
    layout3.push<float>(2);
    
    IndexBuffer ebo3(indices3, 6);
    vao3.addVertexBuffer(vbo3, layout3);
    vao3.addIndexBuffer(ebo3);
    
    
    
    VertexArray vao2;
    VertexBuffer vbo2(vertices2, sizeof(vertices2));
    VertexBufferLayout layout2;
    layout2.push<float>(3);
    layout2.push<float>(2);
    vao2.addVertexBuffer(vbo2, layout2);
    
    
    Texture texture1("res/textures/container.jpg", GL_RGB, true);
    Texture texture2("res/textures/awesomeface.png", GL_RGBA, true);
    
    
    Camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glm::mat4 model(1.0f);
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.4f, 0.0f));
    view = cam.GetViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
    
    //model = glm::mat4(1.0f);
    //view = glm::mat4(1.0f);
    //projection = glm::mat4(1.0f);
    
    shaderProgram.bind();
    //glUniform1i(glGetUniformLocation(shaderProgram.getID() ,"texture1"), 0);
    
    shaderProgram.setFloat("uVisibility3", 1.0f); //get multiple textures working
    shaderProgram.setFloat("uVisibility2", 1.0f);
    texture1.bind(0);
    texture2.bind(1);
    
    /*
     ImGUI setup
     */
    
    /*
     */
    
    
    
    glm::vec4 clearColour = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    renderer.enableDepthTest();
    while(!glfwWindowShouldClose(window))
    {
        renderer.setClearColour(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
        processInput(window);
        renderer.clearColourBuffer();
        renderer.clearDeptBuffer();
        
        
        //  ImGui_ImplGlfw_NewFrame();
        //  ImGui::NewFrame();
        
        
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //turn off wireframe mode
        
        shaderProgram.bind();
        //        shaderProgram.setVec3f("uColour", sin(glfwGetTime()), sin(glfwGetTime()+glm::radians(30.0f)), sin((glfwGetTime())+glm::radians(60.0f)));
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(VAO);
        //renderer.draw(vao3, ebo3, shaderProgram);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //renderer.draw(vao, ebo, shaderProgram);
        //glBindVertexArray(vao2.getID());
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //renderer.draw(vao2, 36, shaderProgram);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Begin("Hey");
        ImGui::ColorEdit3("clear color", (float*)&clearColour);
        ImGui::End();
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        //ImGui::ShowDemoWindow(&show_demo_window);
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    return 0;
}
