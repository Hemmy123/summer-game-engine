#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"




int main(){
    GraphicsNode* graphics = new GraphicsNode;
    
    while(true){
        graphics->update();

    }
    

    
    
    return 0;
}


