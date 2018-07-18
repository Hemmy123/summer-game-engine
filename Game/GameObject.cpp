////========================================
// Class: GameObject
// Author: Hemmy
// Date: 11/07/2018
// Description:
//
// ========================================

#include "GameObject.hpp"


GameObject::GameObject(){
	//TODO: Make UUID here
}

GameObject::GameObject(Vector3 pos, Vector3 rot, Vector3 sca):
m_position(pos),
m_rotation(rot),
m_scale(sca){
	
}

GameObject::~GameObject(){
	// Free/Delete UUID
}


