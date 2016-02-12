//
//  rgbapixel.h
//  rgb
//
//  Created by me on 8/30/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef rgb_rgbapixel_h
#define rgb_rgbapixel_h
#include <cstdint>
using std::uint8_t;

class RGBAPixel
{
public:
    uint8_t 	red;
    uint8_t 	green;
    uint8_t 	blue;
    uint8_t 	alpha;
    RGBAPixel();
    RGBAPixel (uint8_t red, uint8_t green, uint8_t blue);
};
#endif
