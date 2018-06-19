////========================================
// Class: MouseInterface
// Author: Hemmy
// Date: 19/06/2018
// Description:
//
// ========================================

#ifndef MouseInterface_hpp
#define MouseInterface_hpp
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector2.hpp"

class MouseInterface {
public:
	MouseInterface(GLFWwindow* window);
	~MouseInterface();

	void update();
	
	void cursorPositionCallback(GLFWwindow *window, double x, double y);
	
	
private:
	GLFWwindow* m_windowListener;
	
	
	// Curser positions
	Vector2 m_absPosition;
	
	float m_moveSpeed = 3.0f;
	float m_mouseSpeed = 0.005f;
};

#endif /* MouseInterface_hpp */
