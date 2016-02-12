/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    if(theSource.getRows()==0||theSource.getColumns()==0||theTiles.size()==0){
    	return NULL;
    }
    else{
    	MosaicCanvas * out =new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    	vector< Point<3> >  newPoints;
    	std::map<Point<3>,TileImage> myMap;
    	for(size_t i=0;i<theTiles.size();i++){

			double arr[3];
			RGBAPixel aveColor=theTiles[i].getAverageColor();
			arr[0]=(double)aveColor.red;
			arr[1]=(double)aveColor.green;
			arr[2]=(double)aveColor.blue;
			Point<3> point(arr);
			newPoints.push_back(point);
			myMap[point]=theTiles[i];
    	}

    	KDTree<3> tree(newPoints);


    	for(int i=0;i<theSource.getRows();i++){
    		for(int j=0;j<theSource.getColumns();j++){
    			     double arr[3];
    				RGBAPixel aveColor=theSource.getRegionColor(i,j);
    				arr[0]=(double)aveColor.red;
    				arr[1]=(double)aveColor.green;
    				arr[2]=(double)aveColor.blue;
    				Point<3> point(arr);
    				Point<3> outPoint=tree.findNearestNeighbor(point);
					out->setTile(i,j,myMap[outPoint]);
	
    		}
    	}
    	return out;
    }
    

    
}