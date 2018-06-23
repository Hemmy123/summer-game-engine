////========================================
// Class: Camera
// Author: Hemmy
// Date: 09/06/2018
// Description:
//
// ========================================

#include "Camera.hpp"

Camera::Camera(InterfaceHandler* ih):
m_interfaceHandler(ih),
m_yaw(0),
m_pitch(0){
	m_windowListener = m_interfaceHandler->getWindowListener();
}

Camera::Camera(InterfaceHandler* ih,float p, float y, Vector3 pos):
m_interfaceHandler(ih),
m_pitch(p),
m_yaw(y),
m_position(pos){

	m_windowListener = m_interfaceHandler->getWindowListener();
}


void Camera::UpdateCamera(float msec)
{
	m_dt = msec;
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
	
	KeyState s = m_interfaceHandler->getKeyState();
	
	switch(s.m_key){
		case(GLFW_KEY_W): {
			m_position.z -= m_dt * m_speed;
			break;
		case(GLFW_KEY_A):{
			m_position.x -= m_dt * m_speed;
			break;
		}
		case(GLFW_KEY_S):{
			m_position.z += m_dt * m_speed;
			break;
		}
		case(GLFW_KEY_D):{
			m_position.x += m_dt * m_speed;
			break;
		}
		case(GLFW_KEY_SPACE):{
			m_position.y += m_dt * m_speed;
			break;
		}
		case(GLFW_KEY_C):{
			m_position.y -= m_dt * m_speed;
			break;
		}
			
			
		}
	}
	
	
}


Matrix4 Camera::BuildViewMatrix()
{
	std::cout<< "Pitch: "<< m_pitch << "Raw: " << m_yaw << "Position: "<<m_position<< std::endl;
	
	Matrix4 pit = Matrix4::Rotation(-m_pitch, Vector3(1, 0, 0));
	Matrix4 yaw = Matrix4::Rotation(-m_yaw, Vector3(0, 1, 0));
	Matrix4 pos = Matrix4::Translation(-m_position);
	
	return	pit * yaw * pos;
}
