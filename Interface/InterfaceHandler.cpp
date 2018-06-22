////========================================
// Class: InterfaceHandler
// Author: Hemmy
// Date: 20/06/2018
// Description:
//
// ========================================

#include "InterfaceHandler.hpp"

InterfaceHandler::InterfaceHandler(GLFWwindow* window):m_windowListner(window){
	m_mouseInterface = new MouseInterface(window);
	m_keyboardInterface = new KeyboardInterface(window);

}


InterfaceHandler::~InterfaceHandler(){
	delete m_mouseInterface;
	delete m_keyboardInterface;
}

void InterfaceHandler::update(){
	m_mouseInterface->update();
	m_keyboardInterface->update();
}
