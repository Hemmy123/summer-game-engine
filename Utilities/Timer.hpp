////========================================
// Class: Timer
// Author: Hemmy
// Date: 15/06/2018
// Description:
//
// ========================================

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <ctime>

using std::clock;

class Timer{
public:
	Timer();
	~Timer();
	
	float getDelta();
	
private:
	clock_t m_lastRecorded;
	clock_t m_deltaTime;

};


#endif /* Timer_hpp */
