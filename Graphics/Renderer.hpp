//
//  Renderer.hpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "RenderObject.hpp"
#include "Camera.hpp"

#include <vector>

using std::vector;

class Renderer{
public:
    Renderer();
    ~Renderer();
    
    int init();
	
	
	void clearBuffers();
	void swapBuffers();
	
	
	/// This needs to be called after creating a Renderer. This is due
	/// to GLFW requireing a window to get user input. Maybe code should
	/// be restructured to avoid this?
	void createCamera(InterfaceHandler* ih);
	
	// ---------- Rendering ---------- //
	
	/// Carries out the whole rendering process, drawing to scene FBO,
	/// add post processing and then presenting the scene to the screen.
	void renderScene();
	
	///Draws the scene onto the scene FBO. Not the actual screen!
	void drawSceneToFBO();
	
	/// Adds any post-processing stuff onto the scene FBO and then draws
	/// it to the process FBO.
	void drawPostProcess();

	/// Draws a renderObject onto whatever FBO is currently bound.
	void drawRenderObject(const RenderObject &o);

	
	// ---------- Updating ---------- //

	/// The 'master' update method which updates everything in the scene
	/// and then calls the render methods to draw to the screen.
	void update(float msec);
	
	/// Updates the camera and view matrix, and then updates the
	/// Objects via the updateRenderObjects method.
	void updateScene(float msec);
	
	/// Loops through all renderObjects and updates their world transform
	void updateRenderObjects(float msec);

	/// Update the matrices being pushing to shaders via uniforms
	void updateShaderMatrices(Shader* shader);
	
	// ---------- Getters/Setters ---------- //
	
	void setOpaqueObjects(vector<RenderObject*> renderObjects);
	void setTransparentObjects(vector<RenderObject*> renderObjects);
	
	void addRenderObject(RenderObject* renderObject);

	GLint getWidth()const 	{return WIDTH;}
	GLint getHeight()const 	{return HEIGHT;}
	
	GLFWwindow* getWindow() const {return m_window;}



	
	void setProjectionMatrix(Matrix4 proj) {m_projMatrix = proj;}
	
	
	
	// ---------- Post processing test methods ---------- //
	
	void generateFBOTexture();
	
	void setCurrentShader(Shader* s) {m_currentShader = s;}
	
	// ---------- Misc ---------- //
	bool checkWindow() {return glfwWindowShouldClose(m_window);}

protected:
	
	std::string glEnumToString(uint e);
	void checkErrors();
	
	
	float m_dt;
	
	void presentScene();
	
	
	Mesh*	m_quad;
	Shader* m_sceneShader;
	Shader* m_processShader;
	Shader* m_currentShader;
	
	// Our Frame buffer objects
	GLuint m_sceneFBO;
	GLuint m_processFBO;
	
	// Frame Attachments  for FBOs
	GLuint m_buffColourAttachment[2];
	GLuint m_buffDepthAttachment;
	
	
	vector<RenderObject*> m_opaqueObjects;
	vector<RenderObject*> m_transparentObjects;
	
    GLFWwindow *m_window;
    
    const GLint WIDTH;
    const GLint HEIGHT;
	
	int m_actualWidth;
	int m_actualHeight;
    
    // Clear Colour
	Vector4 m_clearColour;

    float m_r = 0.3;
    float m_g = 0.5;
    float m_b = 0.4;
    float m_a = 1;
	
	int n = 10;

	//Matrix4 ortho = Matrix4::Orthographic(-1,6,12,4,2,-2);
	//Matrix4 ortho = Matrix4::Orthographic(-n,n,		n,-n,	n,-n);
	Matrix4 ortho = Matrix4::Orthographic(-n,n,		n,-n,	-n,n);

	
	Matrix4 m_projMatrix;
	Matrix4 m_modelMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_textureMatrix;

	Camera* m_camera;
};




#endif /* Renderer_hpp */
