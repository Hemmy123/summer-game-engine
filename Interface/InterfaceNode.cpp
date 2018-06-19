////========================================
// Class: InterfaceNode
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================



#include "InterfaceNode.hpp"


InterfaceNode::InterfaceNode(GLFWwindow *window, EventBus* bus, SubSystem subSystem):m_windowListener(window), EventNode(bus,subSystem){
	m_mouseInterface 	= new MouseInterface(m_windowListener);
	m_keyboardInterface = new KeyboardInterface(m_windowListener);
	
}

InterfaceNode::~InterfaceNode(){
	
	delete m_mouseInterface;
	delete m_keyboardInterface;
	
	
}

void InterfaceNode::handleEvent(Event event){
	
}

void InterfaceNode::update(){
	
	m_keyboardInterface->update();
	m_mouseInterface->update();
}

