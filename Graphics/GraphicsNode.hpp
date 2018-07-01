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

using std::vector;

class GraphicsNode:public EventNode {
public:
    GraphicsNode(EventBus* eventBus, SubSystem subSystem);
    ~GraphicsNode();
	
	void initOGL();
	void createDemoScene();
	
	void handleEvent(Event event);
	
    void update(float msec);
    
	void renderTriangleTest();
	
	void createCamera(InterfaceHandler* ih) { m_renderer->createCamera(ih);}
	
	GLFWwindow* getWindow() const {return m_renderer->getWindow();}
	
	
private:
	
	void initPerspective();

	
	
	
	
    Renderer *m_renderer;
	
	
	vector<Shader*> 		m_shaders;
	vector<Mesh*>			m_meshes;
	vector<RenderObject*> 	m_renderObjects;
	
	
    Shader* m_testShader;
    Mesh* m_testTriangleMesh;
	RenderObject* m_testRenderObject;
    
};




#endif /* GraphicsNode_hpp */
