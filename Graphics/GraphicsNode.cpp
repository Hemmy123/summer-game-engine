//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

#include "SOIL2.h"

GraphicsNode::GraphicsNode(EventBus* bus, SubSystem subSystem):EventNode(bus,subSystem){
    m_renderer = new Renderer();

	
	initOGL();
	initPerspective();

	createDemoScene();
	
}
void GraphicsNode::initOGL(){
	
	// Cull faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	// Depth test so stuff doesn't render on top of each other;
	glEnable(GL_DEPTH_TEST);

	// Blend func for transparent objects;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
}


void GraphicsNode::initPerspective(){

	float viewDistance = 1000;
	float aspectRatio = (float)m_renderer->getWidth() / (float)m_renderer->getHeight();
	Matrix4 perspective = Matrix4::Perspective(1, viewDistance, aspectRatio, 45.0f);
	
	m_renderer->setProjectionMatrix(perspective);

}

GraphicsNode::~GraphicsNode(){
	
	for(auto shader: m_shaders){
		delete shader;
	}
	
	for(auto mesh: m_meshes){
		delete mesh;
	}
	
	for(auto renderObject: m_renderObjects){
		delete renderObject;
	}
	
	delete m_renderer;

	
	
}

void GraphicsNode::createDemoScene(){

	
	// ----- Create Shaders -----
	string vertexPath ="Assets/Shaders/Vertex/basicVert.glsl";
	string fragPath ="Assets/Shaders/Fragment/texturedFrag.glsl";
	Shader* shader = new Shader(vertexPath.c_str(),fragPath.c_str() );
	m_shaders.push_back(shader);


	// ----- Create Meshes -----
	
	Mesh* mesh1 = Mesh::readObjFileTwo("Assets/Models/Rabbit.obj");
	mesh1->loadTexture("Assets/Textures/Rabbit/Rabbit_D.tga");
	m_meshes.push_back(mesh1);
	mesh1->bufferData();

	
	// ----- Render Objects -----
	
	
	RenderObject* ro1 = new RenderObject(mesh1, shader);
	RenderObject* ro2 = new RenderObject(mesh1, shader);
	RenderObject* ro3 = new RenderObject(mesh1, shader);
	RenderObject* ro4 = new RenderObject(mesh1, shader);

	
	
	Matrix4 const trans1 =  Matrix4::Translation(Vector3(0,0.5,-5));
	Matrix4 const trans2 =  Matrix4::Translation(Vector3(2,0.5,-5));
	Matrix4 const trans3 =  Matrix4::Translation(Vector3(4,0.5,-5));
	Matrix4 const trans4 =  Matrix4::Translation(Vector3(6,0.5,-5));



	
	ro1->setModelMatrix(trans1);
	ro2->setModelMatrix(trans2);
	ro3->setModelMatrix(trans3);
	ro4->setModelMatrix(trans4);

	m_renderer->addRenderObject(ro1);
	m_renderer->addRenderObject(ro2);
	m_renderer->addRenderObject(ro3);
	m_renderer->addRenderObject(ro4);


	
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







