#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"
#include "GameNode.hpp"
#include "EventBus.hpp"



void printGLFWVersion(){
	const char *version =  glfwGetVersionString();
	std::cout<<version<<std::endl;

}


int main(){
	EventBus* bus = new EventBus();
	GameNode* 		game 		= new GameNode(bus,Sys_Game);
    GraphicsNode* 	graphics 	= new GraphicsNode(bus,Sys_Graphics);
	
	printGLFWVersion();
	
	float fakeDT = 0.5;
	
    while(true){
        graphics->update(fakeDT);
		game->update(fakeDT);
		
		
		bus->update();
    }
	
    

	delete bus;
	delete graphics;
    
    return 0;
}


