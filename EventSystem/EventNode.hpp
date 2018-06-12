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
#include "Event.hpp"

class EventNode {
public:
	EventNode(SubSystem system);
	
	//void sendEvent(Event event) { m_eventBus->addEvent(event);}
	
	virtual void handleEvent() = 0;
	
protected:
	
	SubSystem m_system;
};

#endif /* EventNode_hpp */
