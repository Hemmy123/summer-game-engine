////========================================
// Class: Timer
// Author: Hemmy
// Date: 15/06/2018
// Description:
//
// ========================================

#include "Timer.hpp"



Timer::Timer(){
	m_lastRecorded 	= clock();
	m_deltaTime 	= 0;
	
}

Timer::~Timer(){
	
}

float Timer::getDelta(){
	clock_t now = clock();
	double duration = ( now - m_lastRecorded ) / (double) CLOCKS_PER_SEC;
	m_lastRecorded = clock();
	
	return duration * 1000;
	
}



