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

#include "EventNode.hpp"

class GraphicsNode:public EventNode {
public:
    GraphicsNode(EventBus* eventBus, SubSystem subSystem);
    ~GraphicsNode();
	
	void handleEvent(Event event);
	
    void update(float msec);
    
	void renderTriangle();
	
	GLFWwindow* getWindow() const {return m_renderer->getWindow();}
	
	
private:
    Renderer *m_renderer;
	
    Shader* m_testShader;
    Mesh* m_testTriangleMesh;
	
	RenderObject* m_testRenderObject;
    
};




#endif /* GraphicsNode_hpp */
