////========================================
// Class: EventBus
// Author: Hemmy
// Date: 12/06/2018
// Description:
//
// ========================================

#include "EventBus.hpp"

void EventBus::addEvent(Event event){
	m_eventQueue.push(event);
	
}


void EventBus::dispatchEvents(){
	if(!m_eventQueue.empty()){
		Event event = m_eventQueue.front();
		
		
		
	}
	
}

void EventBus::update() { 
    dispatchEvents();
}

void EventBus::addSubsystem(SubSystem system, EventNode *node) { 
	// if subsystem does not exist (cannot be found in map)
	// Add it to the map.
}


