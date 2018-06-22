////========================================
// Class: InterfaceNode
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// Class that handles input from a mouse and keyboard.
// This will currently send out events using the
// event system, however if this is bad, it will
// be used directly by the other subsystems to
// manlipulate objects.
//
// Maybe have most common keys be direct (like movement)
// and send other more uncommon keys (like opening and menu)
// be in the event system?
//
//
// ========================================

#ifndef InterfaceNode_hpp
#define InterfaceNode_hpp

#include "EventBus.hpp"
#include "KeyboardInterface.hpp"
#include "MouseInterface.hpp"

class InterfaceNode: public EventNode{
public:
	InterfaceNode(GLFWwindow *window, EventBus* bus, SubSystem subSystem);
	~InterfaceNode();
	
	void handleEvent(Event event);
	void update();
private:
	
	GLFWwindow* 		m_windowListener;
	KeyboardInterface* 	m_keyboardInterface;
	MouseInterface*		m_mouseInterface;
};
#endif /* InterfaceNode_hpp */
