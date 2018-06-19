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
    
    //void update();
    int init();
    
    void pollEvents();
    void clearBuffers();
    void swapBuffers();
	
	void renderScene();
	void renderRenderObject(const RenderObject &o);

	void updateScene(float msec);
	
	void updateRenderObjects(float msec);

	void updateShaderMatrices(GLuint program);
	
	
	
    bool checkWindow() {return glfwWindowShouldClose(m_window);}

	void setOpaqueObjects(vector<RenderObject*> renderObjects);
	void setTransparentObjects(vector<RenderObject*> renderObjects);
	
	void addRenderObject(RenderObject* renderObject);

	
	void setProjectionMatrix(Matrix4 proj) {m_projMatrix = proj;}
	
	
	GLint getWidth()const 	{return WIDTH;}
	GLint getHeight()const 	{return HEIGHT;}
	
	GLFWwindow* getWindow() const {return m_window;}
	
	
private:
    
	vector<RenderObject*> m_opaqueObjects;
	vector<RenderObject*> m_transparentObjects;
	
    GLFWwindow *m_window;
    
    const GLint WIDTH;
    const GLint HEIGHT;
    
    
    // Clear Colour
    float m_r = 0.3;
    float m_g = 0.5;
    float m_b = 0.4;
    float m_a = 1;
	
	Matrix4 m_projMatrix;
	Matrix4 m_modelMatrix;
	Matrix4 m_viewMatrix;
	Matrix4 m_textureMatrix;

	Camera* m_camera;
};




#endif /* Renderer_hpp */
