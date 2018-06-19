////========================================
// Class: KeyboardInterface
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================

#include "KeyboardInterface.hpp"
#include <iostream>

KeyboardInterface::KeyboardInterface(GLFWwindow *windowListener):m_windowListener(windowListener){
	
	
	glfwSetKeyCallback(m_windowListener, keycallback);
	glfwSetInputMode(m_windowListener, GLFW_STICKY_KEYS, 1);
}

KeyboardInterface::~KeyboardInterface(){
	
}

void KeyboardInterface::update(){
	
}


void KeyboardInterface::keycallback(GLFWwindow *window, int key, int scancode, int action, int mods){
	
	switch(key){
		case GLFW_KEY_SPACE:{
			switch(action){
				case GLFW_PRESS:{
					std::cout<<"Space has been pressed!"<<std::endl;
					break;
				}
				case GLFW_REPEAT:{
					std::cout<<"Space is being held"<<std::endl;
					break;
				}
				case GLFW_RELEASE:{
					std::cout<<"Space has been released!"<<std::endl;
					break;
				}
			
			}
			break;
		}
			
	}
	
	
}

