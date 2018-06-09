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
	
	float fakeDT = 0.5;
	
    while(true){
        graphics->update(fakeDT);

    }
	
    

    
    
    return 0;
}


