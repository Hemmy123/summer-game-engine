////========================================
// Class: MasterRenderer
// Author: Hemmy
// Date: 05/07/2018
// Description:
// Contains the base code to render something
// to the screen. If something fancy is needed
// like post-processing it can derive this class.
// (Similar to NCLGLs OGLRenderer)
//
//
// ========================================


#ifndef MasterRenderer_hpp
#define MasterRenderer_hpp

#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>


#include "Matrix4.hpp"
#include "Shader.hpp"

class MasterRenderer {
public:
	MasterRenderer();
	~MasterRenderer();
	
	virtual void update(float dt) = 0;
	
	virtual void clearBuffers();
	
	virtual void renderScene();
	
	void swapBuffers();
	
	
protected:
	float m_dt;
	
	GLFWwindow *m_window;
	
	const GLint WIDTH;
	const GLint HEIGHT;
	
	int m_actualWidth;		// Dimensions reported by dimensional
	int m_actualHeight;
	
	float m_viewDistance 	= 1000;
	float m_fov 			= 45.0f;
	float m_aspectRatio;
	
	Matrix4 m_ortho;
	Matrix4 m_persp;
	
	Matrix4 m_projMatrix;
	Matrix4 m_modelMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_textureMatrix;
	
};

#endif /* MasterRenderer_hpp */
