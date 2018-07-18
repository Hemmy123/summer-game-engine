////========================================
// Class: GameObject
// Author: Hemmy
// Date: 11/07/2018
// Description:
//
// ========================================

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Vector3.hpp"
#include "Matrix4.hpp"


// Quick and easy tag which defines
// what a gameobject this. This will be
// turned into a proper data driven method
// later as this card coded tag method
// is rather messy

enum ObjectTag{
	T_Player,
	T_Wall,
	T_Playform,
	T_Trigger,
	
};

class GameObject {
public:
	GameObject();
	GameObject(Vector3 pos, Vector3 rot, Vector3 sca);
	
	~GameObject();
	
	
	// ---------- Getters/Setters ---------- //
	inline Vector3 getPosition() 	const { return m_position;}
	inline Vector3 getRotation() 	const { return m_rotation;}
	inline Vector3 getScale() 		const { return m_scale;}
	inline ObjectTag getTag()		const { return m_tag;}

	inline void setPosition(Vector3 p) 	{ m_position = p;};
	inline void setRotation(Vector3 r) 	{ m_rotation = r;};
	inline void setScale(Vector3 s) 	{ m_scale = s;};
	
protected:
	
	char* m_UID;
	
	Vector3 m_position;
	Vector3 m_rotation; // Change to quaternion?
	Vector3 m_scale;
	
	Matrix4 m_modelMatrix;
	
	// What texture/mesh the object should have.
	ObjectTag m_tag;
	
	
};


#endif /* GameObject_hpp */
