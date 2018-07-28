////========================================
// Class: HeightMap
// Author: Hemmy
// Date: 28/07/2018
// Description:
//
// ========================================

#ifndef HeightMap_hpp
#define HeightMap_hpp

#include <stdio.h>
#include "Mesh.hpp"
#include "PerlinNoise.hpp"

class HeightMap:public Mesh{
public:
	
	HeightMap(
	int rawWidth,
	int rawHeight,
	float heightMap_x,
	float heightMap_z,
	float heightMap_y,
	float heightMap_tex_x,
	float heightMap_tex_z,
	PerlinNoise* perlinNoise);
	
	~HeightMap();
	
	void generateFlatTerrain();
	void generateRandomTerrain(Vector3 position,int octaves, float frequency, float persistance );

	
private:
	int m_rawWidth;
	int m_rawHeight;
	
	float m_xMultiplier;
	float m_zMultiplier;
	float m_yMultiplier;
	
	float m_xTexCoord;
	float m_zTexCoord;
	PerlinNoise* m_noiseGenerator;
	
};


#endif /* HeightMap_hpp */
