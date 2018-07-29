//
//  Utils.hpp
//  Maths
//
//  Created by Hemmy on 02/06/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

//#include <math.h> 
#include <cstdlib>
#include <limits>
#include <stdio.h>

static const float  PI = 3.14159265358979323846f;


class MathUtils {
    
public:
    //Degrees to radians
     static inline double DegToRad(const double rad)    {
        return rad * PI / 180.0;
    };
    
	static inline float max(float a, float b) { return  a > b ?  a :  b;};
	static inline float min(float a, float b) { return  a < b ?  a :  b;};
	
	
	static inline float lerp(float a, float b, float t){return a + t * (b - a);}
	
};
#endif /* Utils_hpp */
