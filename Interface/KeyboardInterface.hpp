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

struct KeyState{
	
	KeyState(int key, int action, int mod):
	m_key(key),
	m_action(action),
	m_mod(mod) {};
	
	KeyState(void):
	m_key(GLFW_KEY_UNKNOWN),
	m_action(GLFW_KEY_UNKNOWN),
	m_mod(GLFW_KEY_UNKNOWN) {};
	
	
	
	int m_key;
	int m_action;
	int m_mod;
	
};

class KeyboardInterface {
public:
	KeyboardInterface(GLFWwindow *windowListener);
	~KeyboardInterface();
	void update();
	
	KeyState getKeyState() const {return m_keystate; }
	
private:
	KeyState m_keystate;
	GLFWwindow *m_windowListener;
};


#endif /* KeyboardInterface_hpp */
