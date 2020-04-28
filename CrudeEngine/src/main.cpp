//
//  main.cpp
//  openGLWork
//
//  Created by Hervé Schmit-Veiler on 4/13/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include <iostream>
#include <cstdint>

#include <cmath>
#include <glad/glad.h>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include <stdio.h>



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

    const size_t bufferWidth = 760;
    const size_t bufferHeight = 500;
    const char* glsl_version = "#version 130";
    Renderer renderer;
    renderer.initOpenGL(3, 3, GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    renderer.createWindow(bufferWidth, bufferHeight, "cookie&dummy");
    
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
    
    /*unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);/**/
    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
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
    
    /**
    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);
    
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //colour attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);/**/
    
    VertexArray vao2;
    VertexBuffer vbo2(vertices2, sizeof(vertices2));
    VertexBufferLayout layout2;
    layout2.push<float>(3);
    layout2.push<float>(2);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    // texture coord attribute
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
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
    projection = glm::perspective(glm::radians(45.0f), (float)bufferWidth / (float)bufferHeight, 0.1f, 100.0f);

    
    shaderProgram.bind();
    //glUniform1i(glGetUniformLocation(shaderProgram.getID() ,"texture1"), 0);
    
    shaderProgram.setFloat("uVisibility3", 1.0f); //get multiple textures working
    shaderProgram.setFloat("uVisibility2", 1.0f);
    texture1.bind(0);
    texture2.bind(2);
    
    /*
     ImGUI setup
     */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(renderer.getWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    /*
     */
    

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    renderer.setClearColour(0.2f, 0.3f, 0.3f, 1.0f);
    renderer.enableDepthTest();
    while(!renderer.windowShouldClose())
    {
        processInput(renderer.getWindow());
        renderer.clearColourBuffer();
        renderer.clearDeptBuffer();
        
        ImGui_ImplOpenGL3_NewFrame();
      //  ImGui_ImplGlfw_NewFrame();
      //  ImGui::NewFrame();
        
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;
            
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());/**/

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //turn off wireframe mode
        
        shaderProgram.bind();
//        shaderProgram.setVec3f("uColour", sin(glfwGetTime()), sin(glfwGetTime()+glm::radians(30.0f)), sin((glfwGetTime())+glm::radians(60.0f)));
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        
        //glBindVertexArray(VAO);
        //renderer.draw(vao3, ebo3, shaderProgram);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //renderer.draw(vao, ebo, shaderProgram);
        renderer.draw(vao2, 36, shaderProgram);
        
        renderer.outputFrame();

    }
    
    //glfwTerminate();
    return 0;
}
