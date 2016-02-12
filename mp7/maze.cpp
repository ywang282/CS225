#include "maze.h"
#include <vector>
#include <algorithm>//randshuffel
#include <cstdlib> //rand

//creat an empty maze
int myRandom(int i){
 return std::rand()%i;
}//checked

SquareMaze::SquareMaze(){
	height=0;
	width=0;
	endX=0;
	endY=0;
}
//checked


//helper function
bool SquareMaze::isEmpty(){
	return height==0;
}//checked


//helper function
void SquareMaze::clear(){
	height=0;
	width=0;
	endX=0;
	endY=0;
	for(int i=0;i<(int)maze.size();i++){
		maze[i].clear();
	}
	disjointSets.clear();
}//checked



void SquareMaze::initiate(int width,int height){

	this->width=width;
	this->height=height;
	endX=0;
	endY=0;
	


	for(int i=0;i<width;i++){
		std::vector<Square> inner;
		for(int j=0;j<height;j++){
			Square toPush;
			inner.push_back(toPush);
		}
		maze.push_back(inner);
	}


	for(int y=0;y<height;y++){
		maze[width-1][y].onRightEdge=true;
	}//the last colomn the right is all true

	for(int w=0;w<width;w++){
		maze[w][height-1].onDownEdge=true;
	}//the last colomn the down is all true

	for(int w=0;w<width;w++){
		maze[w][0].onTopEdge=true;
	}//the last colomn the top is all true

	for(int y=0;y<height;y++){
		maze[0][y].onLeftEdge=true;
	}//the last colomn the left is all true

	disjointSets.addelements(width*height);
}
//checked

//random delete all the walls. 
void SquareMaze::randomDeleteWall(){
	std::vector<int> toShuffel;
	for(int i=0;i<width*height;i++){
		toShuffel.push_back(i);
	}//now we have the 25 numbers to shuffel
	std::random_shuffle(toShuffel.begin(),toShuffel.end(),myRandom);
	//now the toShuffel vector is shuffeled. 

	int count=0;//keep track of how many walls we delete

	while(count<width*height-1){
		//start deleting!
		for(int i=0;i<(int)toShuffel.size();i++){
			int indexToDelete=toShuffel[i];
			int xCoordinate;
			int yCoordinate;
			xCoordinate=indexToDelete%width;
			yCoordinate=indexToDelete/width;
			int dir=(rand()%10+1)%2;//1~10
			int one;
			int two;
			if(dir==0&&!maze[xCoordinate][yCoordinate].onRightEdge){
				one=indexToDelete;
				two=indexToDelete+1;
				int rep1=disjointSets.find(one);
				int rep2=disjointSets.find(two);
				if(rep1==rep2){
					//they are already in the same union
				}
				else{
					disjointSets.setunion(rep1,rep2);
					setWall(xCoordinate,yCoordinate,0,false);
					count++;
				}
			}

			else if(dir==0&&maze[xCoordinate][yCoordinate].onRightEdge){
				//dont do anything;
			}
			else if(dir==1&&maze[xCoordinate][yCoordinate].onDownEdge){
				//dont do anything
			}
			else{
				one=indexToDelete;
				two=indexToDelete+width;
				int rep1=disjointSets.find(one);
				int rep2=disjointSets.find(two);
				if(rep1==rep2){
					//they are already in the same union
				}
				else{
					disjointSets.setunion(rep1,rep2);
					setWall(xCoordinate,yCoordinate,1,false);
					count++;
				}
			}
		}//end of for

	}//end of while		
}
//checked

void SquareMaze::setWall(int x,int y,int dir,bool exists){
	if(x>=width||y>=height||x<0||y<0){
		return;
	}
	else{
		if(dir==0){
			maze[x][y].right=exists;
		}
		else{
			maze[x][y].down=exists;
		}
		
	}
}	
//checked

/*Makes a new SquareMaze of the given height and width.*/
void SquareMaze::makeMaze(int width,int height){
	if(!isEmpty()){
		clear();//checked
	}
	initiate(width,height);//checked
	randomDeleteWall();
}
//checked




bool SquareMaze::canTravel(int x,int y,int dir)const{
	
	if(dir==0){
		if(maze[x][y].onRightEdge){
			return false;
		}
		else{
			return !maze[x][y].right;
		}
	}
	else if(dir==1){
		if(maze[x][y].onDownEdge){
			return false;
		}
		else{
			return !maze[x][y].down;
		}
	}else if(dir==2){
		if(maze[x][y].onLeftEdge){
			return false;
		}
		else{
			return !maze[x-1][y].right;
		}
	}else{
		if(maze[x][y].onTopEdge){
			return false;
		}
		else{
			return !maze[x][y-1].down;
		}
	}
}//checked


std::vector<int> SquareMaze::solveMaze(){
	assignDis(0,0,2);//checked
	getBottomBiggest();//checked
	std::vector<int> solution;//checked
	printPath(endX,endY,solution);//checked
	return solution;
}//ckecked

void SquareMaze::printPath(int x,int y,std::vector<int> & solution){
	if(canTravel(x,y,0)&&maze[x+1][y].dis+1==maze[x][y].dis){
		solution.insert(solution.begin(),2);
		printPath(x+1,y,solution);
	}else if(canTravel(x,y,1)&&maze[x][y+1].dis+1==maze[x][y].dis){
		solution.insert(solution.begin(),3);
		printPath(x,y+1,solution);
	}else if(canTravel(x,y,2)&&maze[x-1][y].dis+1==maze[x][y].dis){
		solution.insert(solution.begin(),0);
		printPath(x-1,y,solution);
	}else if(canTravel(x,y,3)&&maze[x][y-1].dis+1==maze[x][y].dis){
		solution.insert(solution.begin(),1);
		printPath(x,y-1,solution);
	}else{
		return;
	}
}//checked

void SquareMaze::getBottomBiggest(){
	int min=0;
	for(int i=0;i<width;i++){
		if(maze[i][height-1].dis>maze[min][height-1].dis){
			min=i;
		}
	}
	endY=height-1;
	endX=min;
}//checked

void SquareMaze::assignDis(int x,int y,int check){
	if(check==0){
		if(canTravel(x,y,1)){
		maze[x][y+1].dis=maze[x][y].dis+1;
		assignDis(x,y+1,3);
		}

		if(canTravel(x,y,2)){
		maze[x-1][y].dis=maze[x][y].dis+1;
		assignDis(x-1,y,0);
		}

		if(canTravel(x,y,3)){
		maze[x][y-1].dis=maze[x][y].dis+1;
		assignDis(x,y-1,1);
		}
	
	}else if(check==1){
		if(canTravel(x,y,0)){
		maze[x+1][y].dis=maze[x][y].dis+1;
		assignDis(x+1,y,2);
		}
		
		if(canTravel(x,y,2)){
		maze[x-1][y].dis=maze[x][y].dis+1;
		assignDis(x-1,y,0);
		}

		if(canTravel(x,y,3)){
		maze[x][y-1].dis=maze[x][y].dis+1;
		assignDis(x,y-1,1);
		}
	}

	else if(check==2){
		if(canTravel(x,y,0)){
		maze[x+1][y].dis=maze[x][y].dis+1;
		assignDis(x+1,y,2);
		}

		if(canTravel(x,y,1)){
		maze[x][y+1].dis=maze[x][y].dis+1;
		assignDis(x,y+1,3);
		}

		if(canTravel(x,y,3)){
		maze[x][y-1].dis=maze[x][y].dis+1;
		assignDis(x,y-1,1);
		}
	}

	else{
		if(canTravel(x,y,0)){
		maze[x+1][y].dis=maze[x][y].dis+1;
		assignDis(x+1,y,2);
		}
		
		if(canTravel(x,y,1)){
		maze[x][y+1].dis=maze[x][y].dis+1;
		assignDis(x,y+1,3);
		}

		if(canTravel(x,y,2)){
		maze[x-1][y].dis=maze[x][y].dis+1;
		assignDis(x-1,y,0);
		}
	}
}//checked


void SquareMaze::blacken(PNG *& source, int x,int y)const{
	RGBAPixel black;
	black.red=0;
	black.green=0;
	black.blue=0;
	black.alpha=255;
	*((*source)(x,y))=black;
}

void SquareMaze::reden(PNG *& source, int x,int y)const{
	RGBAPixel red;
	red.red=255;
	red.green=0;
	red.blue=0;
	red.alpha=255;
	*((*source)(x,y))=red;
}

void SquareMaze::whiten(PNG *& source, int x,int y)const{
	RGBAPixel white;
	white.red=255;
	white.green=255;
	white.blue=255;
	white.alpha=255;
	*((*source)(x,y))=white;
}



PNG * SquareMaze::drawMaze()const{
	PNG * out =new PNG();
	out->resize(width*10+1,height*10+1);

	for(int i=10;i<width*10+1;i++){
		blacken(out,i,0);
	}
	for(int i=0;i<height*10+1;i++){
		blacken(out,0,i);
	}

	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			if(maze[x][y].right){
				for(int k=0;k<=10;k++){
					blacken(out,(x+1)*10,y*10+k);
				}
			}
			if(maze[x][y].down){
				for(int k=0;k<=10;k++){
					blacken(out,x*10+k,(y+1)*10);
				}
			}
		}
	}
	return out;
}//checked


PNG * SquareMaze::drawMazeWithSolution(){
	PNG * out=drawMaze();
	std::pair<int,int> startPoint;
	startPoint.first=5;
	startPoint.second=5;
	std::vector<int> solution=solveMaze();
	for(int i=0;i<(int)solution.size();i++){
		startPoint=drawSolution(startPoint.first,startPoint.second,solution[i],out);
	}

	for(int k=1;k<10;k++){
		whiten(out,endX*10+k,(endY+1)*10);
	}
	return out;
}//checked

std::pair<int,int> SquareMaze::drawSolution(int x,int y,int dir,PNG *& source){
	std::pair<int,int> out;
	if(dir==0){
		for(int i=x;i<=x+10;i++){
			reden(source,i,y);
		}
		out.first=x+10;
		out.second=y;
	}else if(dir==1){
		for(int i=y;i<=y+10;i++){
			reden(source,x,i);
		}
		out.first=x;
		out.second=y+10;
	}else if(dir==2){
		for(int i=x-10;i<=x;i++){
			reden(source,i,y);
		}
		out.first=x-10;
		out.second=y;
	}else{
		for(int i=y-10;i<=y;i++){
			reden(source,x,i);
		}
		out.first=x;
		out.second=y-10;
	}
	return out;
}//checked