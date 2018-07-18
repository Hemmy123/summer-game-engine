////========================================
// Class: Level
// Author: Hemmy
// Date: 11/07/2018
// Description:
//
// ========================================

#ifndef Level_hpp
#define Level_hpp

#include <stdio.h>
#include <vector>
#include "GameObject.hpp"

class Level {
public:
	
	Level();
	~Level();
	
	
	void createDemoLevel();
	
private:
	std::vector<GameObject*> m_gameObjects;
};

#endif /* Level_hpp */
