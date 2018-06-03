//
//  GraphicsNode.cpp
//  Graphics
//
//  Created by Hemmy on 30/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#include "GraphicsNode.hpp"

GraphicsNode::GraphicsNode(){
    m_renderer = new Renderer();
    generateTriangleTest();
}

GraphicsNode::~GraphicsNode(){
    delete m_testShader;
    delete m_renderer;
    
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

}

void GraphicsNode::update(){
    if (!m_renderer->checkWindow()){
        m_renderer->clearBuffers();
        m_renderer->pollEvents();
        m_renderer->renderScene();
        renderTriangle();
        
        
        m_renderer->swapBuffers();
    }
}

void GraphicsNode::generateTriangleTest(){
    string vertexPath ="Assets/Shaders/Vertex/basicVert.glsl";
    string fragPath ="Assets/Shaders/Fragment/basicFrag.glsl";
    
    m_testShader = new Shader(vertexPath.c_str(),fragPath.c_str() );
    
    GLfloat vertices[] =
    {
        -0.5f,  -0.5f,  0.0f, // Bottom left
        0.5f,   -0.5f,  0.0f, // Bottom Right
        0.0f,   0.5f,   0.0f, // Bottom left
    };
    
    // Making VAO and VBO
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    
    //binding VAO;
    
    glBindVertexArray(m_VAO);             // Bind VAO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); // Bind VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);   // Load the vertices
    
    // ??
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat) , (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);               // unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind buffer
    

}

void GraphicsNode::renderTriangle(){
    GLuint program = m_testShader->getProgram();
    glUseProgram(program);
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}







