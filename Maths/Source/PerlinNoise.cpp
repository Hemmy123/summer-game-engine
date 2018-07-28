////========================================
// Class: PerlinNoise
// Author: Hemmy
// Date: 28/07/2018
// Description:
//
// ========================================

#include "PerlinNoise.hpp"
#include "MathUtils.hpp"

PerlinNoise::PerlinNoise(int destScale, int seed) :permutationSize(destScale), destScale(destScale)
{
	generatePermArray(seed,destScale);
}

PerlinNoise::~PerlinNoise(){
}


void PerlinNoise::generatePermArray(int seed, int destScale)
{
	
	// Random Permutation taken from:
	//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
	
	perm.resize(destScale);
	// Fill p with values from 0 to 255
	iota(perm.begin(), perm.end(), 0);
	
	// Initialize a random engine with seed
	std::default_random_engine engine(seed);
	
	// Suffle using the above random engine
	shuffle(perm.begin(), perm.end(), engine);
	
	// Duplicate the permutation vector
	perm.insert(perm.end(), perm.begin(), perm.end());
	
}

Vector2* PerlinNoise::surroundingPointsOf(Vector2 point)
{
	
	Vector2* surroundingPoints = new Vector2[4];
	if (point.x == 0 && point.y == 0) // point is the origin
	{
		Vector2 topLeft = Vector2(0.0f, 1.0f);
		Vector2 topRight = Vector2(1.0f, 1.0f);
		
		Vector2 botRight = Vector2(1.0f, 0.0f);
		Vector2 botLeft = Vector2(0.0f, 0.0f);
		surroundingPoints[0] = topLeft;
		surroundingPoints[1] = topRight;
		surroundingPoints[2] = botLeft;
		surroundingPoints[3] = botRight;
		
		
	}
	
	else if (point.x == 0 && point.y != 0) { // point is along the y axis
		
		float floorY = floor(point.y);
		float ceilY = ceil(point.y);
		
		Vector2 topLeft = Vector2(0.0f, ceilY);
		Vector2 topRight = Vector2(1.0f, ceilY);
		Vector2 botLeft = Vector2(0.0f, floorY);
		Vector2 botRight = Vector2(1.0f, floorY);
		
		surroundingPoints[0] = topLeft;
		surroundingPoints[1] = topRight;
		surroundingPoints[2] = botLeft;
		surroundingPoints[3] = botRight;
		
		
	}
	else if (point.x != 0 && point.y == 0) {// point is along the x axis
		float floorX = floor(point.x);
		float ceilX = ceil(point.x);
		
		Vector2 topLeft = Vector2(floorX, 1.0f);
		Vector2 topRight = Vector2(ceilX, 1.0f);
		Vector2 botLeft = Vector2(floorX, 0.0f);
		Vector2 botRight = Vector2(ceilX, 0.0f);
		surroundingPoints[0] = topLeft;
		surroundingPoints[1] = topRight;
		surroundingPoints[2] = botLeft;
		surroundingPoints[3] = botRight;
		
	}
	else if (point.x != 0 && point.y != 0) {
		
		float floorX = floor(point.x);
		float floorY = floor(point.y);
		float ceilX = ceil(point.x);
		float ceilY = ceil(point.y);
		
		Vector2 topLeft = Vector2(floorX, ceilY);
		Vector2 topRight = Vector2(ceilX, ceilY);
		Vector2 botRight = Vector2(ceilX, floorY);
		Vector2 botLeft = Vector2(floorX, floorY);
		
		surroundingPoints[0] = topLeft;
		surroundingPoints[1] = topRight;
		surroundingPoints[2] = botLeft;
		surroundingPoints[3] = botRight;
		
	}
	else {
		bool a = true;
	}
	return surroundingPoints;
	
}



float PerlinNoise::noiseAt(Vector2 point)
{
	
	//Integer part of float
	int intX = floor(point.x);
	int intY = floor(point.y);
	
	
	// Decimal part of float
	float relativeX = point.x - intX;
	float relativeY = point.y - intY;
	
	float* weights = surroundingWeights(point);
	
	
	// With fading
	float fadeX = fadeFunction(relativeX);
	float fadeY = fadeFunction(relativeY);
	
	float lerpA = MathUtils::lerp(weights[0], weights[1], fadeX);
	float lerpB = MathUtils::lerp(weights[2], weights[3], fadeX);
	float lerpC = MathUtils::lerp(lerpB, lerpA, fadeY);
	
	delete[] weights;
	
	return lerpC;
}

float PerlinNoise::noiseAt(Vector2 point, int octaves, float frequency, float persistence)
{
	
	float freq = frequency;
	float amplitude = 1.0f;
	float total = 0.0f;
	
	for (int i = 0; i < octaves; ++i) {
		float s = (float)destScale / (float)freq;
		
		Vector2 pos = Vector2(point.x / s, point.y / s);
		total += noiseAt(pos) * amplitude;
		
		amplitude *= persistence;
		freq *= 2;
		
	}
	return total;
}


float* PerlinNoise::surroundingWeights(Vector2 point) {
	Vector2* surroundingPoints = surroundingPointsOf(point);
	
	float* weights = new float[4];
	
	for (unsigned i = 0; i < 4; ++i) {
		int x = (surroundingPoints[i].x);
		int y = (surroundingPoints[i].y);
		
		int px = abs(x %permutationSize);
		int py = abs(y %permutationSize);
		
		
		
		int gradIndex = perm[px + perm[py ] ] % 7;
		
		Vector2 gradientVector = randomVectors[gradIndex];
		Vector2 cornerToPoint = surroundingPoints[i] - point ;
		
		float dotProduct = cornerToPoint.dot(gradientVector);
		weights[i] = dotProduct;
	}
	delete[] surroundingPoints;
	return weights;
	
}

float PerlinNoise::fadeFunction(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
