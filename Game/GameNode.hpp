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
#include "InterfaceHandler.hpp"
#include "Level.hpp"

class GameNode:public EventNode {
public:
	GameNode(EventBus* bus, SubSystem subSystem, InterfaceHandler* ih);
	~GameNode();
	void handleEvent(Event event);
	void update(float dt);
	void checkInputs();
	
	bool getEndGame(){return m_endGame;}
	
	
	/* Test Methods */
	void loadTestLevel();
	
private:
	bool m_endGame;
	float m_dt;
	

	Level* m_currentLevel;
	InterfaceHandler* m_interfaceHandler;
	
};

#endif /* GameNode_hpp */
