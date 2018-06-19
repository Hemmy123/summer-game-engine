////========================================
// Class: KeyboardInterface
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================

#ifndef KeyboardInterface_hpp
#define KeyboardInterface_hpp

#include "InterfaceNode.hpp"
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class KeyboardInterface:public InterfaceNode{
public:
	KeyboardInterface(GLFWwindow *windowListener,EventBus* bus, SubSystem subSystem);
	~KeyboardInterface();
	
	void update();
	
	static void keycallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void cursorPositionCallback(GLFWwindow *window, double x, double y);
	
	
private:
	
	// Curser positions
	double m_x;
	double m_y;
	
	float m_moveSpeed = 3.0f;
	float m_mouseSpeed = 0.005f;
	float m_FoV = 45.0f;
	
	GLFWwindow *m_windowListener;
};


#endif /* KeyboardInterface_hpp */
