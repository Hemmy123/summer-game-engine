////========================================
// Class: PhysicsNode
// Author: Hemmy
// Date: 11/09/2018
// Description: Class that handles communication
// between the physics subsystem and the other
// subsystems
//
// ========================================

#ifndef PhysicsNode_hpp
#define PhysicsNode_hpp

#include "EventBus.hpp"
#include <stdio.h>

class PhysicsNode: public EventNode{
public:
	PhysicsNode(EventBus* bus, SubSystem subSystem);
	~PhysicsNode();
	
	void handleEvent(Event event);
	void update(float dt);
	
private:
	
};


#endif /* PhysicsNode_hpp */
