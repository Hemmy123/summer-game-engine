////========================================
// Class: SceneRenderObjects
// Author: Hemmy
// Date: 29/07/2018
// Description:
//
// ========================================

#ifndef SceneRenderObjects_hpp
#define SceneRenderObjects_hpp

#include <stdio.h>
#include "RenderObject.hpp"
#include <vector>

using std::vector;
class SceneRenderObjects{
public:
	void setRenderObjects(vector<RenderObject*> ro);
	void addRenderObject(RenderObject *renderObject);
	
	vector<RenderObject*> getTransparentObjects() 	{ return m_transparentObjects;};
	vector<RenderObject*> getOpaqueObjects()		{ return m_opaqueObjects;};
	
	
private:
	
	vector<RenderObject*> m_transparentObjects;
	vector<RenderObject*> m_opaqueObjects;
	
	
};

#endif /* SceneRenderObjects_hpp */
