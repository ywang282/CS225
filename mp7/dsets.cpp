#include "dsets.h"


void DisjointSets::addelements(int num){
	for(int i=0;i<num;i++){
		upTree.push_back(-1);
	}
}	
/*This function should compress paths and works as described in lecture.*/
int DisjointSets::find(int elem){
	if(upTree[elem]<0){
		return elem;
	}

	return upTree[elem]=find(upTree[elem]);
}	
/*This function should be implemented as union-by-size.

That is, when you setunion two disjoint sets, the smaller 
(in terms of number of nodes) should point at the larger. 
This function works as described in lecture, except that you 
should not assume that the arguments to setunion are roots of 
existing uptrees.

Your setunion function SHOULD find the roots of its arguments 
before combining the trees. If the two sets are the same size, 
make the tree containing the second argument point to the tree 
containing the first. (Note that normally we could break this 
tie arbitrarily, but in this case we want to control things 
for grading.)*/
void DisjointSets::setunion	(int a,int b){
	int root1=find(a);
	int root2=find(b);
	int newSize=upTree[root1]+upTree[root2];
	if(smaller(root1,root2)){
		upTree[root1]=root2;
		upTree[root2]=newSize;

	}else{
		upTree[root2]=root1;
		upTree[root1]=newSize;
	}

}

bool DisjointSets::smaller(int a,int b){
	if(upTree[a]>upTree[b]){
		return true;
	}
	return false;
}	

void DisjointSets::clear(){
	upTree.clear();
}









