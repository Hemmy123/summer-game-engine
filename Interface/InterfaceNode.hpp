////========================================
// Class: InterfaceNode
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================

#ifndef InterfaceNode_hpp
#define InterfaceNode_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include "EventBus.hpp"


class InterfaceNode: public EventNode{
public:
	InterfaceNode(GLFWwindow *window, EventBus* bus, SubSystem subSystem);
	~InterfaceNode();
	
	void handleEvent(Event event);
	virtual void update()= 0;
private:
	
	
	

	
	
	
};
#endif /* InterfaceNode_hpp */
