////========================================
// Class: OBJReader
// Author: Hemmy
// Date: 23/06/2018
// Description:
//	A Very simple OBJ reader taken from
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
// ========================================

#ifndef OBJReader_hpp
#define OBJReader_hpp

#include <stdio.h>
#include <vector>

#include "Vector2.hpp"
#include "Vector3.hpp"
class OBJReader {
	
public:
	OBJReader();
	~OBJReader();
	
	static bool readOBJFile(std::string path,
					 std::vector<Vector3> &out_vertices,
					 std::vector<Vector2> &out_uvs,
					 std::vector<Vector3> &out_normals);
	
private:
	Vector2 test;
	
};

#endif /* OBJReader_hpp */
