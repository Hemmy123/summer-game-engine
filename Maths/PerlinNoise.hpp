////========================================
// Class: PerlinNoise
// Author: Hemmy
// Date: 14/08/2018
// Description:
//
// ========================================

#ifndef PerlinNoise_hpp
#define PerlinNoise_hpp
#include <stdio.h>
#include <vector>

using std::vector;
class PerlinNoise{
public:
	PerlinNoise();
	~PerlinNoise();
	

	float	fadeFunction(float t){return t * t * t * (t * (t * 6 - 15) + 10);};
//	void	generatePermArray(int seed, int destScale);
//	float*	surroundingWeights(Vector2 point);
//	Vector2* surroundingPointsOf(Vector2 point);
//	
//	void setDestScale(int s) { destScale = s; }
//	
	
protected:
	int m_permutationSize;
	int m_destScale;

	vector<int> m_perm;
	
};


#endif /* PerlinNoise_hpp */
