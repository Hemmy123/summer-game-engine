////========================================
// Class: Camera
// Author: Hemmy
// Date: 09/06/2018
// Description:
//
// ========================================

#include "Camera.hpp"


void Camera::UpdateCamera(float msec)
{
	
}

Matrix4 Camera::BuildViewMatrix()
{
	return	Matrix4::Rotation(-m_pitch, Vector3(1, 0, 0)) *
	Matrix4::Rotation(-m_yaw, Vector3(0, 1, 0)) *
	Matrix4::Translation(-m_position);
}
