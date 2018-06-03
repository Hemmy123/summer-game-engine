//
//  Renderer.hpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

class Renderer{
public:
    Renderer();
    ~Renderer();
    
    //void update();
    int init();
    
    void pollEvents();
    void clearBuffers();
    void renderScene();
    void swapBuffers();
    
    
    bool checkWindow() {return glfwWindowShouldClose(m_window);}

private:
    
    
    GLFWwindow *m_window;
    
    const GLint WIDTH;
    const GLint HEIGHT;
    
    
    // Clear Colour
    float m_r = 0.3;
    float m_g = 0.5;
    float m_b = 0.4;
    float m_a = 1;

    
};




#endif /* Renderer_hpp */
