// ========================================
// Class: Timer
// Author: Hemmy
// Date: 15/06/2018
// Description:
//
// ========================================

#ifndef Timer_hpp
#define Timer_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <stdio.h>



class Timer{
public:
	Timer();
	~Timer();
	
	/// returns delta time in MILLISECONDS
	float getDelta();
	
private:
	double m_lastRecorded;
	double m_deltaTime;

};


#endif /* Timer_hpp */
