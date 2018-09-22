#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "GraphicsNode.hpp"
#include "GameNode.hpp"
#include "EventBus.hpp"
#include "Timer.hpp"
#include "PhysicsNode.hpp"

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
	PhysicsNode*		physics 		= new PhysicsNode(bus, Sys_Physics);
	Timer* 				timer 			= new Timer();
	printGLFWVersion();
	
	inputHandler->update();
	
	// 16ms
	const float MAXDT = (1.0f/60.0f) * 1000;
	
    while(!game->getEndGame()){
		
		float frameTime = timer->getDelta();
		//std::cout << "frameTime: " << frameTime <<std::endl;

		while (frameTime > 0){
			float dt = MathUtils::min(frameTime, MAXDT);
//			std::cout << "Inside " << std::endl;
			//std::cout << "frameTime: " << frameTime << " DT: " << dt << std::endl;
			
			inputHandler->update();
			game->update(dt);
			bus->update();
			graphics->update(dt);

			frameTime -= dt;
			
		}

	}

	delete bus;
	delete game;
	delete graphics;
	delete inputHandler;
	delete timer;
	delete physics;
    return 0;
}


