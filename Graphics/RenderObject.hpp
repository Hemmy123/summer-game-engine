////========================================
// Class: RenderObject
// Author: Hemmy
// Date: 03/06/2018
// Description:
//
// ========================================

#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <stdio.h>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Matrix4.hpp"

#include <vector>

using std::vector;


// TODO: Write copy and assignment operators.
class RenderObject {
public:
	RenderObject(void);
	RenderObject(Mesh*m, Shader*s, GLuint t = 0);
	~RenderObject();
	
	
	
	GLuint loadTexture(const string& filename);
	void update(float msec);
	
	void draw() const;
	
	/* ---------- Getters and Setters ---------- */
	Mesh*   getMesh() const			{return m_mesh;}
	void    setMesh(Mesh*m)				{m_mesh = m;}
	
	Shader* getShader() const			{return m_shader; }
	void    setShader(Shader*s)			{m_shader = s;}
	
	GLuint  getTexture() const			{return m_texture;}
	void    setTexture(GLuint tex)  	{m_texture = tex;}
	
	Matrix4 getModelMatrix() const  	{return m_modelMatrix;}
	void    setModelMatrix(Matrix4 mat) {m_modelMatrix = mat;}
	
	Matrix4 getWorldTransform() const 		{ return m_worldTransform; }
	void    setWorldTransform(Matrix4 mat) 	{ m_worldTransform = mat;}
	
	bool 	getTransparent() const 		{ return m_transparent;}
	void 	setTransparent(bool t)		{ m_transparent = t;}
	
	const vector<RenderObject*>& getChildren() const  {return m_children;}
	
	
private:
	char* m_ID;
	
	bool 	m_transparent;
	Shader* m_shader;
	Mesh*   m_mesh;
	
	
	GLuint  m_texture;
	
	Matrix4 m_modelMatrix;
	Matrix4 m_worldTransform;
	
	RenderObject*            m_parent;
	vector<RenderObject*>    m_children;
};



#endif /* RenderObject_hpp */
