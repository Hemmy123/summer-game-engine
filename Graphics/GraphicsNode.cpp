//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

#include "SOIL2.h"

#include "Common.hpp"
GraphicsNode::GraphicsNode(EventBus* bus, SubSystem subSystem):EventNode(bus,subSystem){
    m_renderer = new Renderer(800, 1024);

	//initPerspective();

	createDemoScene();
	
}


void GraphicsNode::initPerspective(){

	
	//m_renderer->setProjectionMatrix(perspective);

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
	string vertexPath 	= SHADERVERTDIR"basicVert.glsl";
	string fragPath 	= SHADERFRAGDIR"texturedFrag.glsl";
	
	string lightingVert = SHADERVERTDIR"lightingVertex.glsl";
	string lightingFrag = SHADERFRAGDIR"lightingFragment.glsl";
	
	//Shader* shader 		= new Shader(vertexPath,fragPath);
	Shader* shader 		= new Shader(lightingVert,lightingFrag);
	m_shaders.push_back(shader);

	Light* testLight = new Light(Vector3(0,5,5) , Vector4(0.5,0.5,0.5,1), 100);
	m_renderer->setShaderLight(shader, *testLight);
	
	// ----- Create Meshes -----
	
	Mesh* mesh1 = Mesh::readObjFile(MODELSDIR"Rabbit.obj");
	Mesh* mesh2 = Mesh::readObjFile(MODELSDIR"cageCube.obj");
	mesh1->loadTexture(TEXTUREDIR"Rabbit/Rabbit_D.tga");
	mesh2->loadTexture(TEXTUREDIR"nyan.jpg");
	mesh2->generateNormals();
	//mesh1->generateNormals();
	
	mesh1->bufferData();
	mesh2->bufferData();

	m_meshes.push_back(mesh1);
	m_meshes.push_back(mesh2);

	// ----- Render Objects -----
	
	RenderObject* ground = new RenderObject(mesh2, shader);

	RenderObject* ro1 = new RenderObject(mesh1, shader);
	RenderObject* ro2 = new RenderObject(mesh1, shader);
	RenderObject* ro3 = new RenderObject(mesh1, shader);
	RenderObject* ro4 = new RenderObject(mesh1, shader);

	// ----- Transformations -----
	
	Matrix4 const trans1 =  Matrix4::Translation(Vector3(0,0.0,-5));
	Matrix4 const trans2 =  Matrix4::Translation(Vector3(2,0.0,-5));
	Matrix4 const trans3 =  Matrix4::Translation(Vector3(4,0.0,-5));
	Matrix4 const trans4 =  Matrix4::Translation(Vector3(6,0.0,-5));


	Matrix4 const cubeScale = Matrix4::Scale(Vector3(1,1,1));
	Matrix4 const cubeTrans = Matrix4::Translation(Vector3(1,-4,-5));
	
	
	ground->setModelMatrix(cubeScale* cubeTrans);
	ro1->setModelMatrix(trans1);
	ro2->setModelMatrix(trans2);
	ro3->setModelMatrix(trans3);
	ro4->setModelMatrix(trans4);

	m_renderer->addRenderObject(ground);
	m_renderer->addRenderObject(ro1);
	m_renderer->addRenderObject(ro2);
	m_renderer->addRenderObject(ro3);
	m_renderer->addRenderObject(ro4);


	
}


void GraphicsNode::update(float msec){
    if (!m_renderer->checkWindow()){
		
		m_renderer->update(msec);
		
    }
}


void GraphicsNode::renderTriangleTest(){
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







