////========================================
// Class: OBJReader
// Author: Hemmy
// Date: 23/06/2018
// Description:
//
// ========================================

#include "OBJReader.hpp"
#include <stdio.h>

OBJReader::OBJReader(){
	
}

OBJReader::~OBJReader(){
	
	
}


bool OBJReader::readOBJFile(std::string path,
							std::vector<Vector3> &out_vertices,
							std::vector<Vector2> &out_uvs,
							std::vector<Vector3> &out_normals,
							std::vector<uint>	 &out_indicies){
	
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	
	// Stores the unordered list of vertices, UVs and normals
	std::vector<Vector3> temp_vertices;
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;
	
	
	// Try to read a file
	FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		printf("Cant open file! !\n");
		return false;
	}
	while(1){
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF){
			break; // EOF = End Of File. Quit the loop.
			return false;
		}
		
		// ----------- Checking the first character of each line ----------- //
	
		// v = vertices
		if ( strcmp( lineHeader, "v" ) == 0 ){
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		
		
		// vt = texture coord
		else if ( strcmp( lineHeader, "vt" ) == 0 ){
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}
		
		// vn = normals
		else if ( strcmp( lineHeader, "vn" ) == 0 ){
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		
		// f = face
		else if ( strcmp( lineHeader, "f" ) == 0 ){
			//std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
								 &vertexIndex[0], &uvIndex[0], &normalIndex[0],
								 &vertexIndex[1], &uvIndex[1], &normalIndex[1],
								 &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
	
		}
	}
	
	
	// TODO: Should I be doing this?
	// Do the same with Tex coords and normals?
	// ONly works because we're using indicies
	out_vertices = temp_vertices;

	for( unsigned int i=0; i<vertexIndices.size(); i++ ){
		
		// Get the indices of its attributes
		unsigned int vertexIndex 	= vertexIndices[i] ;
		unsigned int uvIndex 		= uvIndices[i] ;
		unsigned int normalIndex 	= normalIndices[i] ;
		
		// Get the attributes thanks to the index
		Vector3 vertex 	= temp_vertices[vertexIndex - 1];
		Vector2 uv 		= temp_uvs[uvIndex - 1];
		Vector3 normal 	= temp_normals[normalIndex];
		
		
		// Put the attributes in buffers
		//out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
		out_indicies.push_back(vertexIndex);

		
	}
	
	fclose(file);
	return true;
}
