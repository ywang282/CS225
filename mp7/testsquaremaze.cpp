/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "png.h"


int main()
{ 
   SquareMaze m;
   m.makeMaze(50,50);
   std::cout << "MakeMaze complete" << std::endl;

   PNG* unsolved = m.drawMaze();
   unsolved->writeToFile("unsolved.png");
   delete unsolved;
   std::cout << "drawMaze complete" << std::endl;
   
   vector<int> sol = m.solveMaze();
   std::cout << "solveMaze complete" << std::endl;
   
   PNG* solved = m.drawMazeWithSolution();
   solved->writeToFile("solved.png");
   delete solved;
   std::cout << "drawMazeWithSolution complete" << std::endl;

/*
   SquareMaze ll;
   ll.makeMaze(2,2);
    std::vector<int> lll = ll.solveMaze();
     PNG* solvedwithsolution = ll.drawMazeWithSolution();
   solvedwithsolution->writeToFile("solvedwithsolution.png");*/
   
   return 0;
}

