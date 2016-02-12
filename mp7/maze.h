#include <vector>
#include "dsets.h"
#include "png.h"

class SquareMaze
{
public:
	SquareMaze();
	void setWall(int x,int y,int dir,bool exists);
	void makeMaze(int width,int height);
	bool canTravel(int x,int y,int dir)const;
	std::vector<int> solveMaze();
	PNG * drawMazeWithSolution();
	PNG * drawMaze()const;

	
private:
	class Square
	{
		public:
			Square(){
				dis=0;
				down=true;
				right=true;
				onRightEdge=false;
				onDownEdge=false;
				onTopEdge=false;
				onLeftEdge=false;
			}
			int dis;
			bool down;//true if the wall is to be deleted
			bool right;
			bool onRightEdge;
			bool onDownEdge;
			bool onTopEdge;
			bool onLeftEdge;
	};

	std::vector<std::vector<Square>> maze;

	int height;
	int width;
	int endX;
	int endY;
	DisjointSets disjointSets;


	bool isEmpty();
	void clear();
	void initiate(int width,int height);
	void randomDeleteWall();
	int getRandomWall();
	void printPath(int x,int y,std::vector<int> & solution);
	void getBottomBiggest();
	void assignDis(int x,int y,int check);
	void blacken(PNG *& source, int x,int y)const;
	void reden(PNG *& source, int x,int y)const;
	void whiten(PNG *& source, int x,int y)const;
	
	std::pair<int,int> drawSolution(int x,int y,int dir,PNG *& source);

	
};