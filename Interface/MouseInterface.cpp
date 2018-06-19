////========================================
// Class: MouseInterface
// Author: Hemmy
// Date: 19/06/2018
// Description:
//
// ========================================

#include "MouseInterface.hpp"
#include <iostream>

MouseInterface::MouseInterface(GLFWwindow* window):m_windowListener(window){
//	glfwSetCursorPosCallback(m_windowListener, cursorPositionCallback);
}

MouseInterface::~MouseInterface(){
	
	
}

void MouseInterface::update(){
	double x,y;
	glfwGetCursorPos(m_windowListener, &x, &y);
	m_absPosition.x = (float)x;
	m_absPosition.y = (float)y;
}

void MouseInterface::cursorPositionCallback(GLFWwindow *window, double x, double y){
	

}
