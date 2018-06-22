////========================================
// Class: MouseInterface
// Author: Hemmy
// Date: 19/06/2018
// Description:
//
// ========================================

#include "MouseInterface.hpp"
#include <iostream>

MouseInterface::MouseInterface(GLFWwindow* window):
m_windowListener(window),
m_absPosition(Vector2(0,0)),
m_relativePosition(Vector2(0,0)),
m_lastAbsolute(Vector2(0,0)){
	
	glfwSetInputMode(m_windowListener, GLFW_STICKY_KEYS, 1);
	
	setCallbacks();
}

MouseInterface::~MouseInterface(){
	
	
}

void MouseInterface::update(){
	calculateAbsolutePosition();
	calculateRelativePosition();
}

void MouseInterface::setCallbacks(){
	glfwSetCursorPosCallback(m_windowListener, cursorPositionCallback);
	glfwSetCursorEnterCallback(m_windowListener, cursorEnterCallBack);
	glfwSetInputMode(m_windowListener, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetMouseButtonCallback(m_windowListener, mouseButtonCallBack);
	

}

void MouseInterface::cursorPositionCallback(GLFWwindow *window, double x, double y){
	

}

void MouseInterface::cursorEnterCallBack(GLFWwindow *window, int entered){
	if(entered){
		std::cout<<"Entered mouse callback!" <<std::endl;
	}
	
	
}


void MouseInterface::mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods){
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout <<"The left button has been pressed!" <<std::endl;
	}
}

void MouseInterface::calculateAbsolutePosition(){
	double x,y;
	glfwGetCursorPos(m_windowListener, &x, &y);
	
	
	//Save last position
	m_lastAbsolute = m_absPosition;
	
	// Update new position
	m_absPosition.x = (float)x;
	m_absPosition.y = (float)y;
	


	
}
	


void MouseInterface::calculateRelativePosition(){
	m_relativePosition = m_absPosition - m_lastAbsolute;
	
}
