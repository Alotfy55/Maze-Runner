//
// Created by ziad on ٢٤‏/١١‏/٢٠١٩.
//

#ifndef MAZERUNNER_CLASS_H
#define MAZERUNNER_CLASS_H

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;


class The_Maze {
	int row , coloumn;
	pair <int, int> startingPoint, endingPoint;
	char** Maze;
	bool** visitedPositions;
	///// Generation of the maze 
	void creating_2D_arrays();
	void Generation(); 
	pair < int, int > GetRandomNeighbour(int, int); 
	bool isValid(int i, int j); 
	void ConnectTwoNodes(pair< int, int >, pair < int, int >); 
	void fillMaze();
	void CustomizeShapeOfMaze();
	/////
	void zeroVisitedArray();
	void clear();
public:
	The_Maze();
	~The_Maze();
	void GenerateMaze(); 
	void takeInput(string);
	void printMaze();
	
};



#endif //MAZERUNNER_CLASS_H
