//
//  Renderer.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "Renderer.hpp"


//Renderer::Renderer(): WIDTH(900),HEIGHT(700)
Renderer::Renderer():
WIDTH(1024),
HEIGHT(800),
m_clearColour(Vector4(0.3,0.5,0.4,1)){
    if ( init() != 0){
        std::cout<<"OpenGL Failed to initialize!"<<std::endl;
    };
	
	glClearColor(
		m_clearColour.x, 
		m_clearColour.y, 
		m_clearColour.z, 
		m_clearColour.w);

	m_sceneShader  = new Shader("Assets/Shaders/Vertex/passThroughVertex.glsl","Assets/Shaders/Fragment/sceneFrag.glsl");
	m_processShader = new Shader("Assets/Shaders/Vertex/passThroughVertex.glsl","Assets/Shaders/Fragment/processFrag.glsl");
	
	if(!m_sceneShader->linkProgram() || !m_processShader->linkProgram()){
		std::cout<<"something went wrong!" << std::endl;
	}
	
	m_quad = Mesh::generateQuad();
	m_quad->bufferData();
	
	generateFBOTexture();
	setCurrentShader(m_sceneShader);
	
	
	m_aspectRatio =(float)m_actualWidth / (float)m_actualHeight;
	m_ortho = Matrix4::Orthographic(-10,10,		10,-10,	-10,10);
	m_persp = Matrix4::Perspective(1, m_viewDistance, m_aspectRatio, m_fov);
	
}

Renderer::~Renderer(){
	
	delete m_sceneShader;
	delete m_processShader;
	delete m_quad;
	
	glDeleteTextures(1, &m_buffColourAttachment);
	glDeleteTextures(1, &m_buffDepthAttachment);
	glDeleteFramebuffers(1, &m_sceneFBO);
	glDeleteFramebuffers(1, &m_processFBO);

	
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


void Renderer::update(float msec){
	m_dt = msec;
	
	glfwPollEvents();
	updateScene(m_dt);
	clearBuffers();
	
	renderScene();
	swapBuffers();
	
	
}





void Renderer::createCamera(InterfaceHandler *ih){
	m_camera = new Camera(ih);
}



void Renderer::renderScene(){
	drawSceneToFBO();
	drawPostProcess();
	presentScene();
}


void Renderer::drawSceneToFBO(){
	
	// Makes it so the scene is drawn to m_bufferFBO!
	glBindFramebuffer(GL_FRAMEBUFFER, m_sceneFBO);
	clearBuffers();
	setCurrentShader(m_sceneShader);

	m_projMatrix = m_persp;
	
	updateShaderMatrices(m_currentShader);
	checkErrors();
	

	for(auto iter: m_opaqueObjects){ 		drawRenderObject(*iter); }
	for(auto iter: m_transparentObjects){ 	drawRenderObject(*iter); }
	
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::drawPostProcess(){
	
	/*
	 Adds post processing to the scene.
	 
	 Assuming the scene has been drawn to a FBO, this bindes the
	 processFBO, sets the texture to whatever was drawn before (so
	 the scene) and then applies post processing effect via a shader
	 by calling m_quad->draw()
	 
	 Whatever is drawn is put into m_bufferColourAttachment (I think?)
	 */
	
	// Bind the process FBO
	glBindFramebuffer(GL_FRAMEBUFFER, m_processFBO);

	setCurrentShader(m_processShader);	// Change to our post processing shader
	m_projMatrix = m_ortho;				// Change projection Matrix to orthographic
	m_viewMatrix.ToIdentity();
	updateShaderMatrices(m_currentShader);
	glDisable(GL_DEPTH_TEST);
	
	// Update screen size uniform.
	GLuint screenSizeID = glGetUniformLocation(m_currentShader->getProgram(), "screenSize");
	glUniform2f(screenSizeID, (WIDTH), (HEIGHT));

	GLuint timeID = glGetUniformLocation(m_currentShader->getProgram(), "time");
	glUniform1f(timeID, (float)(glfwGetTime()*10.0f) );
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_buffColourAttachment, 0 );
	m_quad->setTexture(m_buffColourAttachment);
	m_quad->draw();
	
	

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	
	glEnable(GL_DEPTH_TEST);	
}



void Renderer::clearBuffers(){
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
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

void Renderer::drawRenderObject(const RenderObject &o){
	m_modelMatrix = o.getModelMatrix();
	if (o.getShader() && o.getMesh()) {
		GLuint program = o.getShader()->getProgram();
		glUseProgram(program);
		updateShaderMatrices(o.getShader());
		o.draw();
	}
	
	for(auto iter:o.getChildren() ){
		drawRenderObject(*iter);

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

void Renderer::updateShaderMatrices(Shader* shader){
	
	GLuint program = shader->getProgram();
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix")  , 1, false, (float*)&m_modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix")   , 1, false, (float*)&m_viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix")   , 1, false, (float*)&m_projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "textureMatrix"), 1, false, (float*)&m_textureMatrix);
	
	Matrix4 mvp = m_projMatrix * m_viewMatrix * m_modelMatrix;
	
	glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, false, (float*)&mvp);
}



void Renderer::generateFBOTexture(){
	// Generate depth texture
	glGenTextures(1, &m_buffDepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_buffDepthAttachment);
	checkErrors();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 	// clamping to make sure no sampling happens that
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// might distort the edges. (Try turning htis off?)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_actualWidth, m_actualHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	checkErrors();

	// Note:
	// GL_DEPTH24_STENCIL8 and GL_DEPTH_STENCIL because it's a depth texture

	

	glGenTextures(1, &m_buffColourAttachment);
	glBindTexture(GL_TEXTURE_2D, m_buffColourAttachment);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 	// clamping to make sure no sampling happens that
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// might distort the edges. (Try turning htis off?)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_actualWidth, m_actualHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	checkErrors();

	
	
	// Generate FBOs
	glGenFramebuffers(1, &m_sceneFBO);
	glGenFramebuffers(1, &m_processFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_sceneFBO);
	
	// Attaching attachments to sceneFBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 	GL_TEXTURE_2D, m_buffDepthAttachment, 	0);		// Depth attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, 	GL_TEXTURE_2D, m_buffDepthAttachment, 	0);		// Stencil attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 	GL_TEXTURE_2D, m_buffColourAttachment,0);		// Colour attackment (only one?)
	checkErrors();

	
	// Checking if FBO attachment was successful
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER)  != GL_FRAMEBUFFER_COMPLETE || !m_buffDepthAttachment  || !m_buffColourAttachment){

		std::cout << "FBO Attachment failed "<<  std::endl;
		checkErrors();

		return;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::presentScene(){
	
	// unbind framebuffers to render to normal screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkErrors();

	setCurrentShader(m_sceneShader);
	m_projMatrix = m_ortho;
	m_viewMatrix.ToIdentity();
	
	updateShaderMatrices(m_currentShader);
	checkErrors();

	m_quad->setTexture(m_buffColourAttachment);
	m_quad->draw();
	glUseProgram(0);
	checkErrors();

	
}

std::string Renderer::glEnumToString(uint e){
	
	std::string errStr = "Could not convert error enum to string!";
	switch(e){
		case GL_NO_ERROR : {
			errStr = "GL_NO_ERROR";
			break;
		}
		case GL_INVALID_ENUM: {
			errStr = "GL_INVALID_ENUM";
			break;
		}
		case GL_INVALID_VALUE: {
			errStr = "GL_INVALID_VALUE";
			break;
		}
		case GL_INVALID_OPERATION: {
			errStr = "GL_INVALID_OPERATION";
			
		}
		case GL_INVALID_FRAMEBUFFER_OPERATION: {
			errStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		}
		case GL_OUT_OF_MEMORY: {
			errStr = "GL_OUT_OF_MEMORY";
			break;
		}
		case GL_STACK_UNDERFLOW: {
			errStr = "GL_STACK_UNDERFLOW";
			break;
		}
		case GL_STACK_OVERFLOW: {
			errStr = "GL_STACK_OVERFLOW";
			break;
		}

	}
	
	return errStr;
	
	
}


void Renderer::checkErrors(){
	auto error = glGetError();
	if( error != GL_NO_ERROR){
		std::cout<<"Something went wrong! " <<  glEnumToString(error) <<std::endl;
	}
	

}





