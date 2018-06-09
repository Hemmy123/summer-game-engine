////========================================
// Class: RenderObject
// Author: Hemmy
// Date: 03/06/2018
// Description: Represents an object that is
// Rendered onto the screen. Code mostly copied
// and adapted from NCLGL.
//
// ========================================

#include "RenderObject.hpp"
#include "IDGenerator.hpp"

RenderObject::RenderObject():m_transparent(false){
	m_mesh		= nullptr;
	m_shader	= nullptr;
	m_texture 	= NULL;
	m_parent  	= nullptr;
	
	// TODO: Replace new with resource manager call
	m_ID 		= IDGenerator::generateID();

}

RenderObject::RenderObject(Mesh*m, Shader*s, GLuint t):m_transparent(false){
	
	m_mesh		= m;
	m_shader	= s;
	m_texture 	= t;
	m_parent  	= nullptr;
	
	// TODO: Replace new with resource manager call
	m_ID 		= IDGenerator::generateID();
}

RenderObject::~RenderObject(){
	// Do not delete shader and mesh!
	// Other RenderObjects could still be using them!
	
	
	//TODO: if children delete all children.
}



void RenderObject::draw()const {
	if(m_mesh) {
		m_mesh->draw();
	}
}

void RenderObject::update(float msec){
	// If parent, apply parent model matrix
	if(m_parent) {
		m_worldTransform = m_parent->m_modelMatrix * m_modelMatrix;
		//worldTransform = modelMatrix * parent->modelMatrix;
	}
	else {
		m_worldTransform = m_modelMatrix;
	}
	
	// Update children.
	for(auto iter: m_children){
		iter->update(msec);
	}
	
	
}

