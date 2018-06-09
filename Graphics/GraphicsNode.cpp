//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

GraphicsNode::GraphicsNode(){
    m_renderer = new Renderer();
	
	// Create test Mesh
    m_testTriangleMesh = Mesh::generateTriangle();
	m_testTriangleMesh->bufferData();

	// Create test Shaders
	string vertexPath ="Assets/Shaders/Vertex/basicVert.glsl";
	string fragPath ="Assets/Shaders/Fragment/basicFrag.glsl";
	m_testShader = new Shader(vertexPath.c_str(),fragPath.c_str() );

	
	// Create RenderObject
	m_testRenderObject = new RenderObject(m_testTriangleMesh, m_testShader);
	
	Matrix4 const currentPos = m_testRenderObject->getWorldTransform();
	
	Matrix4 const trans =  Matrix4::Translation(Vector3(1,0,0));
	m_testRenderObject->setModelMatrix(trans);
	
	m_renderer->addRenderObject(m_testRenderObject);

}

GraphicsNode::~GraphicsNode(){
    delete m_testShader;
	delete m_testTriangleMesh;
    delete m_renderer;
	
}

void GraphicsNode::update(float msec){
    if (!m_renderer->checkWindow()){
        m_renderer->clearBuffers();
        m_renderer->pollEvents();
		
		m_renderer->updateScene(msec);
		m_renderer->renderScene();
		
       // renderTriangle();
        
        
        m_renderer->swapBuffers();
    }
}


void GraphicsNode::renderTriangle(){
    GLuint program = m_testShader->getProgram();
    glUseProgram(program);
    m_testRenderObject->draw();
  
}







