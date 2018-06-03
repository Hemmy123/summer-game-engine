//
//  Vector4.hpp
//  Maths
//
//  Created by Rich Davison
//  Adapted from NCLGL
#ifndef Vector4_hpp
#define Vector4_hpp

#include <stdio.h>

class Vector4    {
public:
    Vector4(void) {
        x = y = z = w = 1.0f;
    }
    Vector4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    
    ~Vector4(void){}
    
    float x;
    float y;
    float z;
    float w;
};

#endif /* Vector4_hpp */
