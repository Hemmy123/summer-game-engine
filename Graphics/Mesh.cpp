//
//  Mesh.cpp
//  Graphics
//
//  Created by Hemmy on 02/06/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "Mesh.hpp"
#include "tiny_obj_loader.hpp"

#include "OBJReader.hpp"
#include "TinyObjConverter.hpp"

Mesh::Mesh(){
	m_texture = 0;
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
	

	// TODO: Need to delete texture here.
	
	
	
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


// TODO: Clean this method up! It was left so I could quickly test
// lighting and other stuff
Mesh* Mesh::readObjFileTwo(std::string path){
	
	


	tinyobj::attrib_t 					attrib;
	std::vector<tinyobj::shape_t> 		shapes;
	std::vector<tinyobj::material_t> 	materials;
	std::string error;
	
	
	
	std::vector<Vector3> vertices;
	std::vector<Vector2> texCoords;
	std::vector<Vector3> normals;
	
	
	bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &error, path.c_str(),
								NULL, false);
	
	
	
	
	
	if (!error.empty()) {
		std::cerr << error << std::endl;
	}
	
	if (!result) {
		printf("Failed to load/parse .obj.\n");
		//return false;
	}
	
	
	// Loop over shapes
	for( int s = 0; s < shapes.size(); s++){
		int index_offset = 0;
		
		// Loop over faces
		for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			
			// should always be 3 since triangles
			int fv = shapes[s].mesh.num_face_vertices[f];
			

			// Loop over vertices in that face
			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				
				tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
				tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
				tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
				
				Vector3 tempV(vx,vy,vz);
				vertices.push_back(tempV);
				
				tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
				tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
				tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
				
				Vector3 tempN(nx,ny,nz);
				normals.push_back(tempN);
				
				tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
				tinyobj::real_t ty = 1 - attrib.texcoords[2*idx.texcoord_index+1];
				
				Vector2 tempT(tx,ty);
				texCoords.push_back(tempT);
				
			}
			index_offset += fv;
			
			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}
	
	Mesh* m = new Mesh();

	m->m_numVertices = vertices.size();

	m->m_vertices = new Vector3[vertices.size()];
	for(int i = 0 ; i < vertices.size() ; i++){
		m->m_vertices[i] = vertices[i];
	}

	m->m_textureCoords = new Vector2[texCoords.size()];
	for(int i = 0 ; i < texCoords.size() ; i++){
		m->m_textureCoords[i] = texCoords[i];
	}

	m->m_normals = new Vector3[normals.size()];
	for(int i = 0 ; i < normals.size(); i++){
		m->m_normals[i] = normals[i];
	}



	
	
	return m;
}


Mesh* Mesh::readObjFile(std::string path){
	Mesh* m = new Mesh();
	
	
	// TODO: change these to proper arrays for better performance
	std::vector<Vector3> vertices;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;
	std::vector<uint>	 indicies;
	
	
	bool success = OBJReader::readOBJFile(path, vertices, uvs, normals, indicies);
	
	if(success){
		// Cast to stop compiler warning
		m->m_numVertices = static_cast<GLuint>(vertices.size());
		m->m_numIndices = static_cast<GLuint>(indicies.size());

		std::cout<< "Vertices: " << m->m_numVertices<<std::endl;
		std::cout<< "Indicies: " << m->m_numIndices<<std::endl;
		
		
		m->m_vertices = new Vector3[m->m_numVertices];
		for(int i = 0 ; i < m->m_numVertices ; i++){
			m->m_vertices[i] = vertices[i];
		}
		
		m->m_textureCoords = new Vector2[m->m_numIndices];
		for(int i = 0 ; i < m->m_numIndices; i++){
			
			Vector2 coords(uvs[i].x, 1 - uvs[i].y);
			m->m_textureCoords[i] = coords;

			//m->m_textureCoords[i] = uvs[i];
			
//			std::cout<< coords << std::endl;
			
		}
		
		
		m->m_normals = new Vector3[m->m_numVertices];
		for(int i = 0 ; i < m->m_numVertices; i++){
			m->m_normals[i] = normals[i];
		}
		
		// This not needed?
		m->m_colours = new Vector4[m->m_numVertices];
		for(int i = 0 ; i < m->m_numVertices; i++){
			m->m_colours[i] = Vector4(1,0,0,1);
		}
		
		m->m_indices = new GLuint[m->m_numIndices];
		for(int i = 0 ; i < m->m_numIndices; i++){
			m->m_indices[i] = indicies[i];
		}
		
		

		return m;
	} else{
		std::cout<<"OBJ file failed to be parsed!"<<std::endl;
		return m;
	}
	
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
    
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	
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
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
}





