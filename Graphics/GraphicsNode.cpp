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
	RenderObject* obj2  = new RenderObject(m_testTriangleMesh, m_testShader);

	m_renderer->addRenderObject(m_testRenderObject);
	m_renderer->addRenderObject(obj2);

}

GraphicsNode::~GraphicsNode(){
    delete m_testShader;
	delete m_testTriangleMesh;
    delete m_renderer;
	
}

void GraphicsNode::update(){
    if (!m_renderer->checkWindow()){
        m_renderer->clearBuffers();
        m_renderer->pollEvents();
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







