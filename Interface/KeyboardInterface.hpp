////========================================
// Class: KeyboardInterface
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================

#ifndef KeyboardInterface_hpp
#define KeyboardInterface_hpp
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class KeyboardInterface {
public:
	KeyboardInterface(GLFWwindow *windowListener);
	~KeyboardInterface();
	void update();
	
	static void keycallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	
	
	
private:
	
	GLFWwindow *m_windowListener;
};


#endif /* KeyboardInterface_hpp */
