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
m_pitch(0),
m_position(Vector3(0,0,0)){
	m_windowListener = m_interfaceHandler->getWindowListener();
}

Camera::Camera(InterfaceHandler* ih,float p, float y, Vector3 pos):
m_interfaceHandler(ih),
m_pitch(p),
m_yaw(y),
m_position(pos){

	m_windowListener = m_interfaceHandler->getWindowListener();
}


void Camera::updateCamera(float msec)
{
	m_pitch -= (m_interfaceHandler->getMouseRelativePos().y);
	m_yaw 	-= (m_interfaceHandler->getMouseRelativePos().x);
	
	m_pitch = MathUtils::min(m_pitch, 90.f); // Restricts pitch so you cant look over your head
	m_pitch = MathUtils::max(m_pitch, -90.f); // Restricts pitch so you cant look under and behind your head
	
	if (m_yaw < 0){
		m_yaw += 360.0f;
	}
	
	if (m_yaw > 360.0f){
		m_yaw -= 360.0f;
	}
	
	
	KeyState s = m_interfaceHandler->getKeyState();
	
	switch(s.m_key){
		case(GLFW_KEY_W): {
			m_position += Matrix4::Rotation(m_yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(0.0f, 0.0f, -1.0f) * msec * m_movementSpeed;
			break;
		}
		case(GLFW_KEY_A):{
			m_position += Matrix4::Rotation(m_yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(-1.0f, 0.0f, 0.0f) * msec * m_movementSpeed;
			break;
		}
		case(GLFW_KEY_S):{
			m_position -= Matrix4::Rotation(m_yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(0.0f, 0.0f, -1.0f) * msec * m_movementSpeed;
			break;
		}
		case(GLFW_KEY_D):{
			m_position -= Matrix4::Rotation(m_yaw, Vector3(0.0f, 1.0f, 0.0f)) *
			Vector3(-1.0f, 0.0f, 0.0f) * msec * m_movementSpeed;
			break;
		}
		case(GLFW_KEY_SPACE):{
			m_position.y += m_dt * m_movementSpeed;
			break;
		}
		case(GLFW_KEY_C):{
			m_position.y -= m_dt * m_movementSpeed;
			break;
		}
			
	}
}


void Camera::update(float msec){
	m_dt = msec;
	updateCamera(msec);
	
	

}


Matrix4 Camera::BuildViewMatrix()
{	
	Matrix4 pit = Matrix4::Rotation(-m_pitch, Vector3(1, 0, 0));
	Matrix4 yaw = Matrix4::Rotation(-m_yaw, Vector3(0, 1, 0));
	Matrix4 pos = Matrix4::Translation(-m_position);
	
	return	pit * yaw * pos;
}
