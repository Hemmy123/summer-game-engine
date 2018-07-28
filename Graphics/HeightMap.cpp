////========================================
// Class: HeightMap
// Author: Hemmy
// Date: 28/07/2018
// Description:
//
// ========================================

#include "HeightMap.hpp"
HeightMap::HeightMap(
					 int rawWidth,
					 int rawHeight,
					 float heightMap_x,
					 float heightMap_z,
					 float heightMap_y,
					 float heightMap_tex_x,
					 float  heightMap_tex_z):
m_rawWidth(rawWidth),
m_rawHeight(rawHeight),
m_xMultiplier(heightMap_x),
m_zMultiplier(heightMap_z),
m_yMultiplier(heightMap_y),
m_xTexCoord(heightMap_tex_x),
m_zTexCoord(heightMap_tex_z){
	
}

HeightMap::~HeightMap(){
	
}


void HeightMap::generateFlatTerrain(){
	
	m_numVertices	= m_rawWidth * m_rawHeight;
	m_numIndices	= (m_rawWidth - 1) * (m_rawHeight - 1) * 6;
	
	m_vertices		= new Vector3[m_numVertices];
	m_textureCoords = new Vector2[m_numVertices];
	m_indices		= new GLuint[m_numIndices];
	
	for (int x = 0; x < m_rawWidth; ++x) {
		for (int z = 0; z < m_rawHeight; ++z) {
			
			int offset				= (x* m_rawWidth) + z;
			m_vertices[offset]		= Vector3(x * m_xMultiplier, 0 , z * m_zMultiplier);
			m_textureCoords[offset] = Vector2(x * m_xTexCoord, z * m_zTexCoord);
		}
	}
	
	m_numIndices = 0;
	
	for (int x = 0; x < m_rawWidth - 1; ++x) {
		for (int z = 0; z < m_rawHeight - 1; ++z) {
			
			
			int a = (x		* (m_rawWidth)) + z;
			int b = ((x + 1)* (m_rawWidth)) + z;
			int c = ((x + 1)* (m_rawWidth)) + (z + 1);
			int d = (x		* (m_rawWidth)) + (z + 1);
			
			
			m_indices[m_numIndices++] = c;
			m_indices[m_numIndices++] = b;
			m_indices[m_numIndices++] = a;
			
			m_indices[m_numIndices++] = a;
			m_indices[m_numIndices++] = d;
			m_indices[m_numIndices++] = c;
			
		}
		
	}
}




