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
    m_testTriangle = Mesh::generateTriangle();
	m_testTriangle->bufferData();

	// Create test Shaders
	string vertexPath ="Assets/Shaders/Vertex/basicVert.glsl";
	string fragPath ="Assets/Shaders/Fragment/basicFrag.glsl";
	m_testShader = new Shader(vertexPath.c_str(),fragPath.c_str() );

	
	// Create RenderObject
	m_testRenderObject = new RenderObject(m_testTriangle, m_testShader);
	m_renderer->addRenderObject(m_testRenderObject);
	
}

GraphicsNode::~GraphicsNode(){
    delete m_testShader;
    delete m_renderer;
    
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

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







