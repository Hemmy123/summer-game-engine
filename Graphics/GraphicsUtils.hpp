////========================================
// Class: GraphicsUtils
// Author: Hemmy
// Date: 11/07/2018
// Description:
//
// ========================================

#ifndef GraphicsUtils_hpp
#define GraphicsUtils_hpp

#include <stdio.h>
#include <vector>
#include "GameObject.hpp"
class GraphicsUtils {
public:
	
	static void gameObjVecToRenderObj(std::vector<GameObject*> const objs);
	
	
	/// Turns a single GameObject into a RenderObject to
	static void gameObjToRenderObj(GameObject const &gameObj);

	
private:
	

};


#endif /* GraphicsUtils_hpp */
