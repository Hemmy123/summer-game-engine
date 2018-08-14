////========================================
// Class: PerlinNoise3D
// Author: Hemmy
// Date: 09/08/2018
// Description:
//
// ========================================

#ifndef PerlinNoise3D_hpp
#define PerlinNoise3D_hpp
#include "Vector3.hpp"
#include "Vector2.hpp"


#include <stdio.h>
#include <vector>
using std::vector;

class PerlinNoise3D{
public:
	PerlinNoise3D(int destScale, int seed);
	~PerlinNoise3D();
	
	float noiseAt(Vector3 point);
	float noiseAt(Vector3 point, int octaves, float frequency, float persistence);
	
	
	
	float	fadeFunction(float t);
	void	generatePermArray(int seed, int destScale);
	float*	surroundingWeights(Vector3 point);
	Vector3* surroundingPointsOf(Vector3 point);
	
	void setDestScale(int s) { destScale = s; }
	
protected:
	int permutationSize;
	
	vector<int> m_perm; // Permuation Array
	
//	vector<Vector2> randomVectors = {
//		Vector2(1,1),	Vector2(-1,1),
//		Vector2(1,-1),	Vector2(-1,-1),
//		Vector2(0,1),	Vector2(1,0),
//		Vector2(1,-1),	Vector2(-1,0)
//	};
//
	
	vector<Vector3> randomVectors = {
		Vector3(1,1,0),	Vector3(-1,1,0),	Vector3(1,-1,0),	Vector3(-1,-1,0),
		Vector3(1,0,1),	Vector3(-1,0,1), 	Vector3(1,0,-1),	Vector3(-1,0,-1),
		Vector3(0,1,1),	Vector3(0,-1,1),	Vector3(0,1,-1),	Vector3(0,-1,-1)
	};
	
	
	int destScale;
	
	
	
	
};


#endif /* PerlinNoise3D_hpp */
