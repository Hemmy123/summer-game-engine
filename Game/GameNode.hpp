////========================================
// Class: GameNode
// Author: Hemmy
// Date: 14/06/2018
// Description:
//
// ========================================

#ifndef GameNode_hpp
#define GameNode_hpp

#include <stdio.h>
#include "EventBus.hpp"


class GameNode:public EventNode {
public:
	GameNode(EventBus* bus, SubSystem subSystem);
	~GameNode();
	void handleEvent(Event event);
	void update(float dt);
	

private:
	
	float m_dt;
	
};

#endif /* GameNode_hpp */
