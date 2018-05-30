#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsSys.hpp"

const GLint WIDTH = 800;
const GLint HEIGHT = 600;


int initWindow(){
    glfwInit( );
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);   // Trying setting opengl window to 3?
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);   // Setting core profile?
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // For running on Mac
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);            // Can't resize
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenglTest", nullptr, nullptr);
    
//    int screenWidth = 800;
//    int screenHeight = 600;
//
    int screenWidth, screenHeight;
    
    //std::cout<<"Screen Width" << screenWidth << std::endl;
    //std::cout<<"Screen Height" << screenHeight << std::endl;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); // have to do this because of retina mac scaling issue?
    
    if(window == nullptr){
        std::cout<< "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    
    glfwMakeContextCurrent(window);
    
    
    glewExperimental = GL_TRUE;
    
    if(glewInit() != GLEW_OK ){
        std::cout<< "Failed to initlialize GLEW" <<std::endl;
        return -1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    
    GraphicsSys *g = new GraphicsSys();
    
    //std::cout<< g->value <<std::endl;
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
//        glClearColor(0.2f, 0.5f, 0.2f, 1);
        glClearColor(g->r, g->g, g->b, 1);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        
        
        
    }
    
    glfwTerminate();
    
    
        
    return 0;
    
}


int main(){
    
    
    initWindow();
    
    
    return 0;
}


