//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

#include "SOIL2.h"
#include "HeightMap.hpp"
#include "Common.hpp"
#include "PerlinNoise.hpp"
GraphicsNode::GraphicsNode(EventBus* bus, SubSystem subSystem):EventNode(bus,subSystem){
    m_renderer = new Renderer(800, 1024);

	//initPerspective();

	createDemoScene();
	
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

	m_light = new Light(Vector3(0,2,-1) , Vector4(1,1,1,1), 100);


	
	// ----- Create Meshes -----
	int rawWidth = 100;
	int rawHeight = 100;
	float heightMap_x = 1;
	float heightMap_z = 1;
	float heightMap_y = 20;
	float heightMap_tex_x = 1/heightMap_x;
	float heightMap_tex_z = 1/heightMap_z;
	
	PerlinNoise* perlin = new PerlinNoise(rawWidth,10);

	
	
	HeightMap* heightmap = new HeightMap(rawWidth,rawHeight,heightMap_x,heightMap_z, heightMap_y,heightMap_tex_x, heightMap_tex_z,perlin);
	heightmap->generateRandomTerrain(Vector3(0,0,0), 3, 2, 0.5);
	Mesh* mesh1 = Mesh::readObjFile(MODELSDIR"Rabbit.obj");
	Mesh* mesh2 = Mesh::readObjFile(MODELSDIR"cageCube.obj");
	mesh1->loadTexture(TEXTUREDIR"Rabbit/Rabbit_D.tga");
	mesh2->loadTexture(TEXTUREDIR"nyan.jpg");
	heightmap->loadTexture(TEXTUREDIR"nyan.jpg");

	//mesh2->generateNormals();
	//mesh1->generateNormals();
	
	heightmap->generateNormals();

	heightmap->bufferData();
	mesh1->bufferData();
	mesh2->bufferData();

	m_meshes.push_back(mesh1);
	m_meshes.push_back(mesh2);

	// ----- Render Objects -----
	
	
	RenderObject* terrain = new RenderObject(heightmap, shader);

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
	
	Matrix4 const terrainpos = Matrix4::Translation(Vector3(-2,-5,-8));
	
	terrain->setModelMatrix(terrainpos);
	ground->setModelMatrix(cubeScale * cubeTrans);
	ro1->setModelMatrix(trans1);
	ro2->setModelMatrix(trans2);
	ro3->setModelMatrix(trans3);
	ro4->setModelMatrix(trans4);

	
	m_renderObjects.push_back(terrain);
	m_renderObjects.push_back(ground);
	m_renderObjects.push_back(ro1);
	m_renderObjects.push_back(ro2);
	m_renderObjects.push_back(ro3);
	m_renderObjects.push_back(ro4);

	m_renderer->setRenderObjects(m_renderObjects);
		
	
}


void GraphicsNode::update(float msec){
    if (!m_renderer->checkWindow()){
		
		m_renderer->update(msec);
		
		/* --- Temp lighting test --- */
		
		
		for(auto ro: m_renderer->getOpaqueObjects()){
			Shader* shader = ro->getShader();
			
			GLuint program = shader->getProgram();
			m_renderer->setShaderLight(shader, *m_light);

			glUseProgram(program);
			Vector3 cameraPos = m_renderer->getCamera()->GetPosition();
			glUniform3fv(glGetUniformLocation(program, "cameraPos"),1,(float*)&cameraPos);
		}
		
		/* ------------------------- */
		
    }
}


void GraphicsNode::handleEvent(Event event){
	SubSystem sender = event.getSender();
	SubSystem receiver = event.getReceiver();
	std::string type = event.getType();
	
	if(sender ==  Sys_Game && receiver == Sys_Graphics && type == "Test Message!"){
		std::cout<< "Message receieved!"<< std::endl;
		
	}
	
}







