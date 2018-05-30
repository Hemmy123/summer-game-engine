//
//  GraphicsSys.hpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef GraphicsSys_hpp
#define GraphicsSys_hpp

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

const GLint WWIDTH = 800;
const GLint HHEIGHT = 600;

class GraphicsSys{
public:
    GraphicsSys();
    ~GraphicsSys();
    
    void func();
    void init();
    
    
    float r = 0.1;
    float g = 0.6;
    float b = 0.1;

private:
    
    
    
    
};




#endif /* GraphicsSys_hpp */
