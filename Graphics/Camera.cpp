////========================================
// Class: Camera
// Author: Hemmy
// Date: 09/06/2018
// Description:
//
// ========================================

#include "Camera.hpp"

Camera::Camera(GLFWwindow* window):
m_windowListener(window),
m_yaw(0),
m_pitch(0){
	m_interfaceHandler = new InterfaceHandler(window);

}

Camera::Camera(GLFWwindow* window,float p, float y, Vector3 pos):
m_pitch(p),
m_yaw(y),
m_position(pos){
	
	m_interfaceHandler = new InterfaceHandler(window);

	
}


void Camera::UpdateCamera(float msec)
{
	
	updateRotationFromMouse();
	updatePositionFromKeyBoard();
	
	
}

void Camera::updateRotationFromMouse(){
	// updates rotation based on the mouse movement
	
	m_pitch -= (m_interfaceHandler->getMouseRelativePos().y);
	m_yaw 	-= (m_interfaceHandler->getMouseRelativePos().x);

	
	m_pitch = fmin(m_pitch, 90.f); // Restricts pitch so you cant look over your head
	m_pitch = fmax(m_pitch, -90.f); // Restricts pitch so you cant look under and behind your head
	

	if (m_yaw < 0)
	{
		m_yaw += 360.0f;
	}
	
	if (m_yaw > 360.0f)
	{
		m_yaw -= 360.0f;
	}


	
}

void Camera::updatePositionFromKeyBoard(){
	// Updates Position based on keyboard input.
	
	
	
	
}


Matrix4 Camera::BuildViewMatrix()
{
	Matrix4 pit = Matrix4::Rotation(-m_pitch, Vector3(1, 0, 0));
	Matrix4 yaw = Matrix4::Rotation(-m_yaw, Vector3(0, 1, 0));
	Matrix4 pos = Matrix4::Translation(-m_position);
	
	return	pit * yaw * pos;
}
