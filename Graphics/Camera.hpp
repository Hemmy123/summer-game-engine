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

class Camera {
	
public:
	Camera(void): m_yaw(0), m_pitch(0){};
	
	Camera(float p, float y, Vector3 pos):m_pitch(p), m_yaw(y),m_position(pos) {}
	
	~Camera(void) {};
	
	void	UpdateCamera(float msec);
	Matrix4 BuildViewMatrix();
	
	Vector3 GetPosition() const { return m_position; }
	void	setPosition(Vector3 val) { m_position = val; }
	
	float	getYaw() const { return m_yaw; }
	void	setYaw(float y) { m_yaw = y; }
	
	float	getPitch()	const { return m_pitch; }
	void	setPitch(float p) { m_pitch = p; }
	
	float	getSpeed() const { return m_speed; }
	void	setSpeed(float s) { m_speed = s; }
private:
	
	float m_yaw;			// Y (Left right)
	float m_pitch;			// X (Up Down)
	Vector3 m_position;
	float m_speed = 50;
};

#endif /* Camera_hpp */
