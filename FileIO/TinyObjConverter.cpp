////========================================
// Class: TinyObjConverter
// Author: Hemmy
// Date: 30/06/2018
// Description:
//
// ========================================

#include "TinyObjConverter.hpp"



vector<Vector3> TinyObjConverter::linearToVec3(vector<float> lin){
	
	vector<Vector3> parsedVec3;
	for(int i = 0 ; i < lin.size() ;  i = i + 3){
		Vector3 temp(lin[i],lin[i+1], lin[i+2]);
		parsedVec3.push_back(temp);
	}
	
	return parsedVec3;
}

vector<Vector2> TinyObjConverter::linearToVec2(vector<float> lin){
	vector<Vector2> parsedVec2;
	for(int i = 0 ; i < lin.size() ;  i = i + 2){
		Vector2 temp(lin[i],lin[i+1]);
		parsedVec2.push_back(temp);
	}
	return parsedVec2;
	
	
}

