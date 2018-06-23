////========================================
// Class: GameNode
// Author: Hemmy
// Date: 14/06/2018
// Description:
//
// ========================================

#include "GameNode.hpp"

GameNode::GameNode(EventBus* bus,SubSystem subSystem, InterfaceHandler* ih):
EventNode(bus,subSystem),
m_endGame(false),
m_interfaceHandler(ih){
	
}


GameNode::~GameNode(){}

void GameNode::update(float dt){
	m_dt = dt;
	checkInputs();
	
}

void GameNode::checkInputs(){
	KeyState s = m_interfaceHandler->getKeyState();
	
	switch(s.m_key){
		case(GLFW_KEY_ESCAPE): {
			m_endGame = true;

		}
	}
}



void GameNode::handleEvent(Event e){

	
}
