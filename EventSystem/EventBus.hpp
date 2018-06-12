////========================================
// Class: EventBus
// Author: Hemmy
// Date: 12/06/2018
// Description:
//
// ========================================

#ifndef EventBus_hpp
#define EventBus_hpp

#include <stdio.h>
#include <queue>
#include <map>
#include "Event.hpp"
#include "EventNode.hpp"


// NOTE: Subsystems are linked to the bus, not the other way around
// like the in old system! (So subsystems do not contain a reference
// the main event bus. The main event bus however contains a reference
// to all of the other sub systems.
class EventBus{
public:
	
	// Adds a subsystem to the map of nodes the EventBus can send
	// messages to.
	void addSubsystem(SubSystem system, EventNode* node);
	void addEvent(Event event);
	void update();
	
protected:
	
	void dispatchEvents();
	EventNode* node;
	
	std::queue<Event> m_eventQueue;
	std::map<SubSystem, EventNode*> m_subsystems;
};


#endif /* EventBus_hpp */
