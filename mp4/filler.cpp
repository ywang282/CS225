/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    
    solidColorPicker sp=solidColorPicker(fillColor);
    return fill(img,x,y,sp,tolerance,frameFreq);
    
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    gridColorPicker gp=gridColorPicker(gridColor,gridSpacing);
    return fill(img,x,y,gp,tolerance,frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    gradientColorPicker gp=gradientColorPicker(fadeColor1,fadeColor2,radius,x,y);
    return fill(img,x,y,gp,tolerance,frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    return filler::fill<Stack>(img,x,y,fillColor,tolerance,frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
     
    solidColorPicker sp=solidColorPicker(fillColor);
    return fill(img,x,y,sp,tolerance,frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
   gridColorPicker gp=gridColorPicker(gridColor,gridSpacing);
   return fill(img,x,y,gp,tolerance,frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    gradientColorPicker gp=gradientColorPicker(fadeColor1,fadeColor2,radius,x,y);
    return fill(img,x,y,gp,tolerance,frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    
    return filler::fill<Queue>(img,x,y,fillColor,tolerance,frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    
    		int count=0;
    		animation animation;
    		int width=img.width();
    		int height=img.height();
    		width=(int)width;
    		height=(int)height;
    		
    		
    		uint8_t OriginalRed=img(x,y)->red;
    		uint8_t OriginalGreen=img(x,y)->green;
    		uint8_t OriginalBlue=img(x,y)->blue;
    		
    		
    		
    		
    		
    		
    		bool processed[width][height];//initialize the boolean array to false;
    		for(int i=0;i<width;i++){
    			for(int j=0;j<height;j++){
    				processed[i][j]=false;
    			}
    		
    		}
    		
    OrderingStructure<int> xx;
    OrderingStructure<int> yy;
    
    xx.add(x);
    yy.add(y);
    
    while(!xx.isEmpty()&&!yy.isEmpty()){
    	int currX=xx.remove();
   	int currY=yy.remove();
    	
    	uint8_t currentRed=img(currX,currY)->red;
    	uint8_t currentGreen=img(currX,currY)->green;
    	uint8_t currentBlue=img(currX,currY)->blue;
    	
    	if(!processed[currX][currY] && (pow(currentRed-OriginalRed,2)+
    		pow(currentGreen-OriginalGreen,2)+pow(currentBlue-OriginalBlue,2)
    			-tolerance<=0)){
    		
    		processed[currX][currY]=true;
    		*img(currX,currY)=fillColor(currX,currY);
    		
    		count++;
    		
    		if(currX+1<width){
    		 	xx.add(currX+1);
    			yy.add(currY);
    		}
    		
    		if(currY+1<height){
    		 	xx.add(currX);
    			yy.add(currY+1);
    		}
    		
    		if(currX-1>=0){
    		 	xx.add(currX-1);
    			yy.add(currY);
    		}
    		
    		if(currY-1>=0){
    		 	xx.add(currX);
    			yy.add(currY-1);
    		}
    		
    		if(count%frameFreq==0){
    			animation.addFrame(img);
    		}
    	}
    }
  		return animation; 
}


