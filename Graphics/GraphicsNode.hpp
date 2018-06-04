//
//  GraphicsNode.hpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef GraphicsNode_hpp
#define GraphicsNode_hpp

#include <stdio.h>
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "RenderObject.hpp"

class GraphicsNode {
public:
    GraphicsNode();
    ~GraphicsNode();
    
    void update();
    
	void renderTriangle();
    
private:
    Renderer *m_renderer;
	
    Shader* m_testShader;
    Mesh* m_testTriangleMesh;
	
	RenderObject* m_testRenderObject;
    
};




#endif /* GraphicsNode_hpp */
