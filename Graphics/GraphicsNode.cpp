//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

GraphicsNode::GraphicsNode(EventBus* bus, SubSystem subSystem):EventNode(bus,subSystem){
    m_renderer = new Renderer();
	// Set Perspective/Ortha Matrix
	float viewDistance = 1000;
	float aspectRatio = (float)m_renderer->getWidth() / (float)m_renderer->getHeight();
	Matrix4 perspective = Matrix4::Perspective(1, viewDistance, aspectRatio, 45.0f);
	
	m_renderer->setProjectionMatrix(perspective);

	
	// Create test Mesh
//    m_testTriangleMesh = Mesh::generateTriangle();
	m_testTriangleMesh = Mesh::readObjFile("Assets/Models/cola.OBJ");
	
	
	m_testTriangleMesh->bufferData();

	// Create test Shaders
	string vertexPath ="Assets/Shaders/Vertex/basicVert.glsl";
	string fragPath ="Assets/Shaders/Fragment/basicFrag.glsl";
	m_testShader = new Shader(vertexPath.c_str(),fragPath.c_str() );

	
	// Create RenderObject
	m_testRenderObject = new RenderObject(m_testTriangleMesh, m_testShader);
	
	Matrix4 const currentPos = m_testRenderObject->getWorldTransform();
	
	Matrix4 const trans =  Matrix4::Translation(Vector3(0,0.5,-5));
	
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
		
		m_renderer->pollEvents();
		m_renderer->updateScene(msec);

		
        m_renderer->clearBuffers();
		m_renderer->renderScene();
        m_renderer->swapBuffers();
    }
}


void GraphicsNode::renderTriangle(){
    GLuint program = m_testShader->getProgram();
    glUseProgram(program);
    m_testRenderObject->draw();
  
}

void GraphicsNode::handleEvent(Event event){
	SubSystem sender = event.getSender();
	SubSystem receiver = event.getReceiver();
	std::string type = event.getType();
	
	if(sender ==  Sys_Game && receiver == Sys_Graphics && type == "Test Message!"){
		std::cout<< "Message receieved!"<< std::endl;
		
	}
	
}







