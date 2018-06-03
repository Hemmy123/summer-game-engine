//
//  Shader.hpp
//  Graphics
//
//  Created by Hemmy on 31/05/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//
#define GLEW_STATIC
#include <GL/glew.h>


#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
/**
 Some of the IO code taken from:
https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
*/
using std::string;
class Shader{
public:
    
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();
    
    string readFile(const char* filePath);
    GLuint loadVertexAndFrag(const char *vertex_path, const char *fragment_path);
    
    
    
    void checkShader(GLuint shader);
    
    
    GLuint getProgram() {return m_program;};
private:
    
    GLuint m_program;
    
};
 

#endif /* Shader_hpp */
