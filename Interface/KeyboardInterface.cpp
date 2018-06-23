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
	}

KeyboardInterface::~KeyboardInterface(){
	
}

void KeyboardInterface::update(){
	if (glfwGetKey( m_windowListener, GLFW_KEY_DOWN ) == GLFW_PRESS){
		m_keystate = KeyState(GLFW_KEY_LAST, GLFW_PRESS, GLFW_KEY_UNKNOWN);
	}
	
}




