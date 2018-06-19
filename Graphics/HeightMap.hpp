////========================================
// Class: HeightMap
// Author: Hemmy
// Date: 16/06/2018
// Description:
//
// ========================================

#ifndef HeightMap_hpp
#define HeightMap_hpp

#include <stdio.h>

class HeightMap {
public:
	HeightMap();
	~HeightMap();
	
	void generateFlatHeightMap();
	
private:
	int m_rawWidth;
	int m_rawHeight;
	
	float m_xMultiplier;
	float m_zMultiplier;
	float m_yMultiplier;
	
	float m_xTexCoord;
	float m_zTexCoord;
};

#endif /* HeightMap_hpp */
