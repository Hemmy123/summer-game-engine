//
//  Utils.hpp
//  Maths
//
//  Created by Hemmy on 02/06/2018.
//  Copyright © 2018 Hemmy. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>

static const float  PI = 3.14159265358979323846f;


class Utils {
    
public:
    //Degrees to radians
     static inline double DegToRad(const double rad)    {
        return rad * PI / 180.0;
    };
    
    
};
#endif /* Utils_hpp */
