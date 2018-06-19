////========================================
// Class: GameNode
// Author: Hemmy
// Date: 14/06/2018
// Description:
//
// ========================================

#include "GameNode.hpp"

GameNode::GameNode(EventBus* bus,SubSystem subSystem):EventNode(bus,subSystem){
	
}


void GameNode::update(float dt){
	m_dt = dt;

	
}

void GameNode::handleEvent(Event dt){
	
	
}
