////========================================
// Class: MasterRenderer
// Author: Hemmy
// Date: 05/07/2018
// Description:
//
// ========================================

#include "MasterRenderer.hpp"


int MasterRenderer::init(){
	glfwInit( );
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Trying setting opengl window to 3?
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);   // Setting core profile?
	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // For running on Mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                       // Can't resize
	m_window = glfwCreateWindow(WIDTH, HEIGHT, "OpenglTest", nullptr, nullptr);
	
	glfwGetFramebufferSize(m_window, &m_actualWidth, &m_actualHeight); // have to do this because of retina mac scaling issue?
	if(m_window == nullptr){
		std::cout<< "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	
	glfwMakeContextCurrent(m_window);
	glewExperimental = GL_TRUE;
	
	if(glewInit() != GLEW_OK ){
		std::cout<< "Failed to initlialize GLEW" <<std::endl;
		return -1;
	}
	
	glViewport(0, 0, m_actualWidth, m_actualHeight);
	
	
	// Cull faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Depth test so stuff doesn't render on top of each other;
	glEnable(GL_DEPTH_TEST);
	
	// Blend func for transparent objects;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	
	
	return 0;
}

void MasterRenderer::clearBuffers(){
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}


void MasterRenderer::swapBuffers(){
	glfwSwapBuffers(m_window);
}
