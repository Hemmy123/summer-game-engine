////========================================
// Class: Camera
// Author: Hemmy
// Date: 09/06/2018
// Description:
//
// ========================================

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include "Vector3.hpp"
#include "Matrix4.hpp"

#include "InterfaceHandler.hpp"

class Camera {
	
public:
	Camera(InterfaceHandler* ih);
	
	Camera(InterfaceHandler* ih,float p, float y, Vector3 pos);
	
	~Camera(void) {};
	
	void	UpdateCamera(float msec);
	
	
	void 	update(float msec);
	// Updates rotation and position from user input.
	// Theses methods tend to be used for debugging as
	// the player wil probably not control the camera
	// directly like this. 
	void 	updateRotationFromMouse();
	void 	updatePositionFromKeyBoard();
	
	
	
	Matrix4 BuildViewMatrix();
	
	Vector3 GetPosition() const { return m_position; }
	void	setPosition(Vector3 val) { m_position = val; }
	
	float	getYaw() const { return m_yaw; }
	void	setYaw(float y) { m_yaw = y; }
	
	float	getPitch()	const { return m_pitch; }
	void	setPitch(float p) { m_pitch = p; }
	
	float	getSpeed() const { return m_movementSpeed; }
	void	setSpeed(float s) { m_movementSpeed = s; }
private:
	float m_dt;
	
	InterfaceHandler* m_interfaceHandler;
	GLFWwindow* m_windowListener;
	float m_yaw;			// Y (Left right)
	float m_pitch;			// X (Up Down)
	Vector3 m_position;
	float m_movementSpeed = 1;
};

#endif /* Camera_hpp */
