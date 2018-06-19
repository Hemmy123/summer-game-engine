#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"
#include "GameNode.hpp"
#include "EventBus.hpp"
#include "Timer.hpp"
#include "KeyboardInterface.hpp"

void printGLFWVersion(){
	const char *version =  glfwGetVersionString();
	std::cout<<version<<std::endl;

}


int main(){
	EventBus* bus = new EventBus();
	GameNode* 		game 		= new GameNode(bus,Sys_Game);
    GraphicsNode* 	graphics 	= new GraphicsNode(bus,Sys_Graphics);
	KeyboardInterface* keyboard  = new KeyboardInterface(graphics->getWindow(), bus, Sys_Interface);
	
	Timer* 			timer 		= new Timer();
	printGLFWVersion();
	
	
	float dt = timer->getDelta();
    while(true){
		
        graphics->update(dt);
		game->update(dt);
		
		bus->update();
		
		dt = timer->getDelta();
    }
	
    

	delete bus;
	delete graphics;
    
    return 0;
}


