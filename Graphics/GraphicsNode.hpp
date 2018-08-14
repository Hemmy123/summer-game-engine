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
#include "GameObject.hpp"

#include "EventNode.hpp"
#include "HeightMap.hpp"


using std::vector;

class GraphicsNode:public EventNode {
public:
    GraphicsNode(EventBus* eventBus, SubSystem subSystem);
    ~GraphicsNode();
	
	void initOGL();
	void createDemoScene();
	void handleEvent(Event event);
    void update(float msec);
	void createCamera(InterfaceHandler* ih) { m_renderer->createCamera(ih);}
	
	GLFWwindow* getWindow() const {return m_renderer->getWindow();}
	
	
private:
	
    Renderer *m_renderer;
	
	/*----- Testing ------------*/
	
	HeightMap* m_heightMap;
	float counter = 0;
	PerlinNoise3D* m_perlin3D;
	/*--------------------------*/

	
	
	vector<Shader*> 		m_shaders;
	vector<Mesh*>			m_meshes;
	vector<RenderObject*> 	m_renderObjects;
	vector<Light*>			m_lights;
	
	Light* 		m_light;

    
};




#endif /* GraphicsNode_hpp */
