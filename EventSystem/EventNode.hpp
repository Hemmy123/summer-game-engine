////========================================
// Class: EventNode
// Author: Hemmy
// Date: 12/06/2018
// Description:
//
// ========================================

#ifndef EventNode_hpp
#define EventNode_hpp

#include <stdio.h>
#include "EventBus.hpp"

class EventBus;

class EventNode {
public:
	EventNode(EventBus* eventBus,SubSystem system);
		
	virtual void handleEvent(Event event) = 0;
	
protected:
	EventBus * m_bus;
	SubSystem m_system;
};

#endif /* EventNode_hpp */
