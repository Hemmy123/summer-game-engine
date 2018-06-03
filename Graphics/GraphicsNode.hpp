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

class GraphicsNode {
public:
    GraphicsNode();
    ~GraphicsNode();
    
    void update();
    
    
    void generateTriangleTest();
    void renderTriangle();
    
private:
    Renderer *m_renderer;
    
    GLuint m_VAO;
    GLuint m_VBO;
    Shader* m_testShader;
    
};




#endif /* GraphicsNode_hpp */