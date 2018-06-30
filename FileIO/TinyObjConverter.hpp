////========================================
// Class: TinyObjConverter
// Author: Hemmy
// Date: 30/06/2018
// Description:
//
// Converts the data formats used in the
// tiny_obj_loader to one that is used in
// this engine (Vector3, Mesh etc...)
// ========================================

#ifndef TinyObjConverter_hpp
#define TinyObjConverter_hpp

#include <stdio.h>
#include "tiny_obj_loader.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include <vector>

using std::vector;


struct MeshData{
	vector<Vector3> m_vertices;
	vector<Vector2> m_texCoords;
	vector<Vector3> m_normals;
	vector<int>		m_indicies;
	
};

class  TinyObjConverter{
public:
	
	static vector<Vector3> linearToVec3(vector<float> lin);
	static vector<Vector2> linearToVec2(vector<float> lin);

	
	
	
private:
	
	
	
};


#endif /* TinyObjConverter_hpp */
