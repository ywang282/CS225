//
//  rgbapixel.cpp
//  rgb
//
//  Created by me on 8/30/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "rgbapixel.h"
#include <string>
RGBAPixel::RGBAPixel(){
    red=255;
    green=255;
    blue=255;
    alpha=255;
}

RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b){
	red = r;
	green = g;
	blue = b;
	alpha = 255;

}
