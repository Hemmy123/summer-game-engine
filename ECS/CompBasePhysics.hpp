////========================================
// Class: CompBasePhysics
// Author: Hemmy
// Date: 30/08/2018
// Description:
//
// ========================================

#ifndef CompBasePhysics_hpp
#define CompBasePhysics_hpp

#include <stdio.h>

struct CompBasePhysics: public Component  {
	float 	m_mass;
	float	m_acceleration;
	Vector3 m_position;
	Vector3 m_velocity;
};



#endif /* CompBasePhysics_hpp */
