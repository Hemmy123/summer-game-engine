#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"
#include "GameNode.hpp"
#include "EventBus.hpp"
#include "Timer.hpp"

void printGLFWVersion(){
	const char *version =  glfwGetVersionString();
	std::cout<<version<<std::endl;

}


int main(){
	EventBus* 			bus 			= new EventBus();
    GraphicsNode* 		graphics 		= new GraphicsNode(bus,Sys_Graphics);
	InterfaceHandler* 	inputHandler 	= new InterfaceHandler(graphics->getWindow());
	graphics->createCamera(inputHandler);
	GameNode* 			game 			= new GameNode(bus,Sys_Game,inputHandler);
	Timer* 				timer 			= new Timer();
	//printGLFWVersion();
	
	inputHandler->update();
	
	
	//float dt = timer->getDelta();
	const float MAXDT = 1/60;
	
    while(!game->getEndGame()){
		float frameTime = timer->getDelta();
		
		while (frameTime > 0){
			float dt = MathUtils::min(frameTime, MAXDT);

			
			inputHandler->update();
			graphics->update(dt);
			game->update(dt);
			bus->update();
			frameTime -= dt;

		}
	}
	
    

	delete bus;
	delete game;
	delete graphics;
	delete inputHandler;
	delete timer;

    return 0;
}


