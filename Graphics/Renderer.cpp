//
//  Renderer.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "Renderer.hpp"


Renderer::Renderer(): WIDTH(800),HEIGHT(600)
{
    if ( init() != 0){
        std::cout<<"OpenGL Failed to initialize!"<<std::endl;
    };
    
    
}

Renderer::~Renderer(){
    glfwTerminate();
    
}


int Renderer::init(){
    
    glfwInit( );
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Trying setting opengl window to 3?
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);   // Setting core profile?
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // For running on Mac
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                       // Can't resize
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "OpenglTest", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight); // have to do this because of retina mac scaling issue?
    
    if(m_window == nullptr){
        std::cout<< "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_window);
    glewExperimental = GL_TRUE;
    
    if(glewInit() != GLEW_OK ){
        std::cout<< "Failed to initlialize GLEW" <<std::endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
   
    return 0;
    
    
}


void Renderer::pollEvents(){
    glfwPollEvents();
}

void Renderer::clearBuffers(){
    glClearColor(m_r, m_g, m_b, m_a);
    glClear(GL_COLOR_BUFFER_BIT);

}

void Renderer::renderScene(){
    // Render triangles n' shit here
}

void Renderer::swapBuffers(){
    glfwSwapBuffers(m_window);
}








