//
//  main.cpp
//  rgb
//
//  Created by me on 8/30/14.
//  Copyright (c) 2014 me. All rights reserved.
//
#include "png.h"
#include "rgbapixel.h"
#include <stdio.h>
#include <string>

using namespace std;

int main() {
    
    
	PNG input("in.png");
	size_t height = input.height();
	size_t width = input.width();
	PNG out = PNG(width, height);
    for (size_t x = 0; x < width; x++) {
        
		for (size_t y = 0; y < height; y++) {
			
			*out.operator()(x,y) = *input.operator()(width-x-1, height-y-1);
        }
    }
            out.writeToFile("out.png");
    
}
