//
//  Mesh.cpp
//  Graphics
//
//  Created by Hemmy on 02/06/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "Mesh.hpp"


Mesh::Mesh(){
    m_numVertices = 0;
	m_type = GL_TRIANGLES;

    for(int i = 0; i < MAX_BUFFER; ++i) {
        m_VBO[i] = 0;
    }
	m_numIndices	= 0;
	m_vertices		= nullptr;
	m_textureCoords	= nullptr;
	m_normals		= nullptr;
	m_tangents		= nullptr;
	m_indices		= nullptr;
	m_colours		= nullptr;
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_VAO);            //Delete our VAO
    glDeleteBuffers(MAX_BUFFER, m_VBO);        //Delete our VBOs
    
    //Later tutorial stuff
    delete[]m_vertices;
    delete[]m_colours;
    delete[]m_textureCoords;
    delete[]m_normals;
    delete[]m_tangents;
    delete[]m_indices;
    
}

Mesh* Mesh::generateTriangle(){
    Mesh* m = new Mesh();
	m->m_numVertices = 3;

	m->m_vertices = new Vector3[m->m_numVertices];
	m->m_vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m->m_vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m->m_vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

	m->m_textureCoords = new Vector2[m->m_numVertices];
	m->m_textureCoords[0] = Vector2(0.5f, 0.0f);
	m->m_textureCoords[1] = Vector2(1.0f, 1.0f);
	m->m_textureCoords[2] = Vector2(0.0f, 1.0f);

	m->m_colours = new Vector4[m->m_numVertices];
	m->m_colours[0] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	m->m_colours[1] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	m->m_colours[2] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	return m;
}

void Mesh::bufferData(){
    glGenVertexArrays(1, &m_VAO);
    
    glBindVertexArray(m_VAO);
    
    //Buffer vertex data
    glGenBuffers(1, &m_VBO[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector3), m_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);


    
    //Buffer texture data
    if (m_textureCoords) {
        glGenBuffers(1, &m_VBO[TEXTURE_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TEXTURE_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector2), m_textureCoords, GL_STATIC_DRAW);
        glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(TEXTURE_BUFFER);
    }
    
    //buffer colour data
    if (m_colours) {
        glGenBuffers(1, &m_VBO[COLOUR_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[COLOUR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(Vector4), m_colours, GL_STATIC_DRAW);
        glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOUR_BUFFER);
    }
    
    //buffer index data
    if (m_indices) {
        glGenBuffers(1, &m_VBO[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(GLuint), m_indices, GL_STATIC_DRAW);
    }
    
    //Once we're done with the vertex buffer binding, we can unbind the VAO,
    //ready to reapply later, such as in the Draw function above!
    glBindVertexArray(0);
}

void Mesh::draw(){
    
  
    glBindVertexArray(m_VAO);

    // If we're using indices:
    if(m_VBO[INDEX_BUFFER]) {
        glDrawElements(m_type, m_numIndices, GL_UNSIGNED_INT, 0);
    }
    else{
        // Else just use vertices
        glDrawArrays(m_type, 0, m_numVertices);    //Draw the triangle!
    }
    // Unbind for good practice
    glBindVertexArray(0);
    
}





