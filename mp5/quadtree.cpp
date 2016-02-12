// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <iostream>
using namespace std;
//a constructor that builds an empty tree;
Quadtree::Quadtree(){
	root=NULL;
	length=0;
}


//destructor that frees the memory;
Quadtree::~Quadtree(){

	clear(root);
	root=NULL;
}

//clear helper function for the destructor;
void Quadtree::clear(Quadtree::QuadtreeNode * croot){
	if(croot==NULL){
		return;
	}	
		clear(croot->nwChild);
		clear(croot->neChild);
		clear(croot->swChild);
		clear(croot->seChild);	
		delete croot;
		croot=NULL;
}

//construct a tree of width and height of resolution and of a source PNG;
Quadtree::Quadtree(const PNG & source, int resolution){
	root=NULL;
	buildTree(source,resolution);
}

// copy constructor;
Quadtree::Quadtree(Quadtree const & other){
	length=other.length;
	root=copy(other.root);
}

//copy constructor helper function;
Quadtree:: QuadtreeNode * Quadtree:: copy( const Quadtree::QuadtreeNode * other)const{
	Quadtree::QuadtreeNode * node;
	if(other==NULL){
		node=NULL;
	}
	else{
		node=new Quadtree::QuadtreeNode(other->element);
		node->nwChild=copy(other->nwChild);
		node->neChild=copy(other->neChild);
		node->swChild=copy(other->swChild);
		node->seChild=copy(other->seChild);
	}
	return node;
}


/*compute the average pixel value*/
RGBAPixel Quadtree::ave(Quadtree::QuadtreeNode * se,Quadtree::QuadtreeNode * sw,
					Quadtree::QuadtreeNode * ne,Quadtree::QuadtreeNode * nw){
	RGBAPixel out;
	
		out.red=(uint8_t)(((int)(se->element.red)+
						(int)(sw->element.red)+
						(int)(ne->element.red)+
						(int)(nw->element.red)
						)/4);
		out.green=(uint8_t)(((int)(se->element.green)+
						(int)(sw->element.green)+
						(int)(ne->element.green)+
						(int)(nw->element.green)
						)/4);
		out.blue=(uint8_t)(((int)(se->element.blue)+
						(int)(sw->element.blue)+
						(int)(ne->element.blue)+
						(int)(nw->element.blue)
						)/4);
	
	
	return out;	
}

Quadtree const & Quadtree::operator=(Quadtree const & other){
	 if(this!=&other){
		clear(root);
		this->length=other.length;
		root=copy(other.root);
	}
	return *this;
}
	
//wrapper build tree function;
void Quadtree::buildTree(PNG const & source,int resolution){
	
	clear(root);//Deletes the current contents of this Quadtree object
	
	length=resolution;//set the width and length to resolution;
	buildTree(source,resolution,root,0,0);//call the helper function;
}

void Quadtree::buildTree(PNG const & source,int resolution,Quadtree::QuadtreeNode *& node,int x,int y){	
	//base case, put the pixel in the leaf;
	if(resolution==1){
		node=new Quadtree::QuadtreeNode(*source(x,y));
		return;
	}
	else{	
		node=new Quadtree::QuadtreeNode();
		/*recurvely build the ewns quadtreenodes*/
		buildTree(source,resolution/2,node->nwChild,x,y);
		buildTree(source,resolution/2,node->neChild,x+resolution/2,y);
		buildTree(source,resolution/2,node->swChild,x,y+resolution/2);
		buildTree(source,resolution/2,node->seChild,x+resolution/2,y+resolution/2);
		node->element=ave(node->nwChild,node->neChild,node->swChild,node->seChild);
	}
}


RGBAPixel Quadtree::getPixel(int x,int y) const{
	if(x>=length||y>=length||y<0||x<0||root==NULL){
		return RGBAPixel();
	}
	else{
		return getPixel(root,x,y,length,0,0);
	}

}
/* traverse down teh tree and get the pixel*/
RGBAPixel Quadtree::getPixel(Quadtree::QuadtreeNode * node,int x,int y,int resolution,int startX,int startY) const{	
	if(node->seChild==NULL){//base case;
		return node->element;
	}
	else{
		if(node!=NULL){//recurvily get the pixel;
			if(x<startX+resolution/2 && y<startY+resolution/2){
				return getPixel(node->nwChild,x,y,resolution/2,startX,startY);
			}
			else if(x>=startX+resolution/2 && y<startY+resolution/2){
				return getPixel(node->neChild,x,y,resolution/2,startX+resolution/2,startY);
			}
			else if(x<startX+resolution/2 && y>=startY+resolution/2){
				return getPixel(node->swChild,x,y,resolution/2,startX,startY+resolution/2);
			}else {
				return getPixel(node->seChild,x,y,resolution/2,startX+resolution/2,startY+resolution/2);
			}
		}
	return RGBAPixel();//************************************************************************************************************************
	}
}

/*decompass a tree*/
PNG Quadtree::decompress() const{
	if(this->root==NULL){
		return PNG();
	}
	else{
		PNG out;
		out.resize(length,length);
		decompress(root,out,0,0,length);
	
		return out;
	}
}

void Quadtree::decompress(Quadtree::QuadtreeNode * node,PNG & source,int x, int y,int resolution)const{
	 if( node->seChild==NULL){
	 	for(int i=0;i<resolution;i++)
	 	{
	 		for(int j=0;j<resolution;j++)
	 		{
	 			*source(x+i,y+j)=node->element;
	 		}
	 	}
	 	
	 	return;
	 }
	 else{
	 	decompress(node->nwChild,source,x,y,resolution/2);
	 	decompress(node->neChild,source,x+resolution/2,y,resolution/2);
	 	decompress(node->swChild,source,x,y+resolution/2,resolution/2);
	 	decompress(node->seChild,source,x+resolution/2,y+resolution/2,resolution/2);
	 }


}

void Quadtree::clockwiseRotate(){
	clockwiseRotate(root);

}

void Quadtree::clockwiseRotate(Quadtree::QuadtreeNode * node){
	if(node==NULL){
		return;
	}
	else{
		Quadtree::QuadtreeNode* nw=node->nwChild;
		Quadtree::QuadtreeNode* ne=node->neChild;
		Quadtree::QuadtreeNode* sw=node->swChild;
		Quadtree::QuadtreeNode* se=node->seChild;

		node->nwChild=sw;
		node->neChild=nw;
		node->swChild=se;
		node->seChild=ne;

		clockwiseRotate(node->nwChild);
		clockwiseRotate(node->neChild);
		clockwiseRotate(node->swChild);
		clockwiseRotate(node->seChild);

	}

}

void Quadtree::prune(int tolerance){
	prune(root,tolerance);
}

void Quadtree::prune(Quadtree::QuadtreeNode * node,int tolerance){
	if(node==NULL){
		return;
	}

	if(node->nwChild==NULL){
		return;
	}
	if(canprune(node,node,tolerance)){
		clear(node->nwChild);
		clear(node->neChild);
		clear(node->swChild);
		clear(node->seChild);

		node->nwChild=NULL;
		node->neChild=NULL;
		node->swChild=NULL;
		node->seChild=NULL;
	}
	else{
		
		prune(node->nwChild,tolerance);
		prune(node->neChild,tolerance);
		prune(node->swChild,tolerance);
		prune(node->seChild,tolerance);
	}
}

bool Quadtree::canprune(Quadtree::QuadtreeNode * mom, Quadtree::QuadtreeNode * child,int tolerance){
	if(child->nwChild==NULL){
		return pixeldiff(mom,child)<=tolerance;
	}
	

		bool b1,b2,b3,b4;

		b1=canprune(mom,child->nwChild,tolerance);
	
		b2=canprune(mom,child->neChild,tolerance);
	
		b3=canprune(mom,child->swChild,tolerance);
		
		b4=canprune(mom,child->seChild,tolerance);
		
		return b1&&b2&&b3&&b4;
	
	
}


int Quadtree::pixeldiff(Quadtree::QuadtreeNode * node1,Quadtree::QuadtreeNode * node2){
	
	int red=((int)(node1->element.red)-(int)(node2->element.red))*((int)(node1->element.red)-(int)(node2->element.red));
	int green=((int)(node1->element.green)-(int)(node2->element.green))*((int)(node1->element.green)-(int)(node2->element.green));
	int blue=((int)(node1->element.blue)-(int)(node2->element.blue))*((int)(node1->element.blue)-(int)(node2->element.blue));
	
	return red+green+blue;
}

int Quadtree::pruneSize	(int tolerance)	const{
		return pruneSize(root,tolerance);
}

int Quadtree::pruneSize(Quadtree::QuadtreeNode * node,int tolerance)const{
	if(node==NULL){
		return 0;
	}
	Quadtree c;
	c.length=length;
	c.root=copy(root);
	c.prune(tolerance);

	return countNode(c.root);
	
}

 int Quadtree::countNode(Quadtree::QuadtreeNode * node)const{
 	if(node->nwChild==NULL){
 		return 1;
 	}
 	return countNode(node->nwChild)+countNode(node->neChild)
 		+countNode(node->swChild)+countNode(node->seChild);
 }


int Quadtree::idealPrune(int numLeaves)	const{
	int max=(255*255)*3;
	int min=0;
	return idealPrune(numLeaves,min,max,0);
}

int Quadtree::idealPrune(int numLeaves,int min, int max,int decrementor)const{
	
	if(pruneSize(max)>numLeaves){
		return max+1;
	}

	if(min>=max){
		return min;
	}

	if(decrementor==1){
		return idealPrune(numLeaves,min,max-1,1);
	}
	
	int mid=(min+max)/2;

	int compare=pruneSize(mid);
	
	
	if(compare<numLeaves) {
		return idealPrune(numLeaves,min,mid,0);
	}
	else if(compare>numLeaves)
	{
		return idealPrune(numLeaves,mid+1,max,0);
	} 
	else{
		return idealPrune(numLeaves,min,mid,1);
	}
	
}///////TA help!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
