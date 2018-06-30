//
//  Renderer.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "Renderer.hpp"


Renderer::Renderer(): WIDTH(800),HEIGHT(600)
{
    if ( init() != 0){
        std::cout<<"OpenGL Failed to initialize!"<<std::endl;
    };
	
}

Renderer::~Renderer(){
    glfwTerminate();
	delete m_camera;
    
}


int Renderer::init(){
    
    glfwInit( );
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // Trying setting opengl window to 3?
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);   // Setting core profile?
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // For running on Mac
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                       // Can't resize
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "OpenglTest", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight); // have to do this because of retina mac scaling issue?
    
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
    
    glViewport(0, 0, screenWidth, screenHeight);
	

	
    return 0;
    
    
}


void Renderer::createCamera(InterfaceHandler *ih){
	m_camera = new Camera(ih);
	
}

void Renderer::pollEvents(){
    glfwPollEvents();
}

void Renderer::clearBuffers(){
    glClearColor(m_r, m_g, m_b, m_a);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}

void Renderer::renderScene(){
	
	
	for(auto iter: m_opaqueObjects){
		renderRenderObject(*iter);
	}
	
	for(auto iter: m_transparentObjects){
		renderRenderObject(*iter);
	}
	
}

void Renderer::swapBuffers(){
    glfwSwapBuffers(m_window);
}

void Renderer::addRenderObject(RenderObject *renderObject){
	if(renderObject->getTransparent()){
		m_transparentObjects.push_back(renderObject);
	} else{
		m_opaqueObjects.push_back(renderObject);
	}
}

void Renderer::renderRenderObject(const RenderObject &o){
	m_modelMatrix = o.getModelMatrix();
	if (o.getShader() && o.getMesh()) {
		GLuint program = o.getShader()->getProgram();
		glUseProgram(program);
		updateShaderMatrices(program);
		o.draw();
	}
	
	for(auto iter:o.getChildren() ){
		renderRenderObject(*iter);

	}

}


void Renderer::updateScene(float msec){
	if(m_camera == nullptr){
		std::cout<<"No camera has been created/set" <<std::endl;
	} else{
		m_camera->UpdateCamera(msec);
		m_viewMatrix = m_camera->BuildViewMatrix();
		updateRenderObjects(msec);
	}
	

}

void Renderer::updateRenderObjects(float msec){

	for(auto iter:m_opaqueObjects ){
		iter->update(msec);
	}
	
	for(auto iter:m_transparentObjects){
		iter->update(msec);
	}
	
	
}

void Renderer::updateShaderMatrices(GLuint program){
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix")  , 1, false, (float*)&m_modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix")   , 1, false, (float*)&m_viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix")   , 1, false, (float*)&m_projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "textureMatrix"), 1, false, (float*)&m_textureMatrix);
	
	Matrix4 mvp = m_projMatrix * m_viewMatrix * m_modelMatrix;
	
	glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, false, (float*)&mvp);
}







