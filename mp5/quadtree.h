// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public: 
		Quadtree();
		~Quadtree();
		Quadtree(const PNG & source, int resolution);		
		Quadtree(Quadtree const & other);
		Quadtree const & operator=(Quadtree const & other);
		void buildTree(PNG const & source,int resolution);
		RGBAPixel getPixel(int x,int y) const;
		PNG decompress() const;
		
		int pruneSize	(	int 	tolerance	)	 const;
		void clockwiseRotate	(		);

void prune	(	int 	tolerance	);

int idealPrune	(	int 	numLeaves	)	 const;

		

	private:
		
	class QuadtreeNode
	{
		public:
		QuadtreeNode(){
			nwChild=NULL;
			neChild=NULL;
			swChild=NULL;
			seChild=NULL;
			//aaa=0;
			//element=color;
		}
		QuadtreeNode(RGBAPixel color){
			nwChild=NULL;
			neChild=NULL;
			swChild=NULL;
			seChild=NULL;
			element=color;
			//aaa=0;
		}
		
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child
		RGBAPixel element;  // the pixel stored as this node's "data"

		//int aaa;
	};
	
	
	QuadtreeNode* root;    // pointer to root of quadtree
	int length;
	
	
	void clear(QuadtreeNode * croot);
	QuadtreeNode * copy( const QuadtreeNode * other) const;
	RGBAPixel ave(QuadtreeNode * se,QuadtreeNode * sw,QuadtreeNode * ne,QuadtreeNode * nw);
	void buildTree(PNG const & source,int resolution,QuadtreeNode *& node,int x,int y);
	RGBAPixel getPixel(QuadtreeNode * node,int x,int y,int resolution,int startX,int startY) const;	
					
	void decompress(QuadtreeNode * node,PNG  & source,int x, int y,int resolution)const;
	void clockwiseRotate(QuadtreeNode * node);
	
void prune(QuadtreeNode * node,int tolerance);
bool canprune(QuadtreeNode * mom, QuadtreeNode * child, int tolerance);
int pixeldiff( QuadtreeNode * node1,QuadtreeNode * node2);
int pruneSize(QuadtreeNode * node,int tolerance)const;
int countNode(QuadtreeNode * node) const;
int idealPrune(int numLeaves,int min, int max,int decrementor)const;

	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
