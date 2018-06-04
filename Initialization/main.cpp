#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"

void printGLFWVersion(){
	const char *version =  glfwGetVersionString();
	std::cout<<version<<std::endl;

}


int main(){
    GraphicsNode* graphics = new GraphicsNode;
	
	printGLFWVersion();
    while(true){
        graphics->update();

    }
	
    

    
    
    return 0;
}


