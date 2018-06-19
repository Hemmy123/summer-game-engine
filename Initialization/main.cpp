#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"
#include "GameNode.hpp"
#include "EventBus.hpp"
#include "Timer.hpp"
#include "InterfaceNode.hpp"

void printGLFWVersion(){
	const char *version =  glfwGetVersionString();
	std::cout<<version<<std::endl;

}


int main(){
	EventBus* bus = new EventBus();
	GameNode* 		game 		= new GameNode(bus,Sys_Game);
    GraphicsNode* 	graphics 	= new GraphicsNode(bus,Sys_Graphics);
	InterfaceNode* 	inputHandler = new InterfaceNode(graphics->getWindow(), bus, Sys_Interface);
	
	Timer* 			timer 		= new Timer();
	printGLFWVersion();
	
	
	float dt = timer->getDelta();
    while(true){
		
        graphics->update(dt);
		game->update(dt);
		inputHandler->update();
		bus->update();
		
		dt = timer->getDelta();
    }
	
    

//	delete bus;
//	delete game;
//	delete graphics;
//	delete inputHandler;
//	delete timer;

    return 0;
}


