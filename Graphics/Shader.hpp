//
//  Shader.hpp
//  Graphics
//
//  Created by Hemmy on 31/05/2018.
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
#include "Light.hpp"
/**
IO code taken from:
https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
*/


enum ShaderStage {
	SHADER_VERTEX = 0,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_TCS,
	SHADER_TES,
	SHADER_MAX
};


using std::string;
class Shader{
public:
    
    Shader(string vertex_path, string fragment_path);
    ~Shader();
    
    string readFile(const char* filePath);
    GLuint loadVertexAndFrag(const char *vertex_path, const char *fragment_path);
    
	bool linkProgram();
    
    void checkShader(GLuint shader);
	void bindAttributes();
    
    GLuint getProgram() {return m_program;};
	
	bool getLinkSuccess()	const{return m_linkSuccess;}
private:
	
	bool	m_linkSuccess;
    GLuint 	m_program;
    
};
 

#endif /* Shader_hpp */
