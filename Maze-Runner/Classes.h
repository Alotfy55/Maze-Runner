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
	void creating_2D_arrays();
	void Generation(); 
	pair < int, int > GetRandomNeighbour(int, int); 
	bool isValid(int i, int j); 
	void ConnectTwoNodes(pair< int, int >, pair < int, int >); 
	void fillMaze();
	void CustomizeShapeOfMaze();  
public:
	void GenerateMaze(); 
	The_Maze();
	void takeInput(string);
	void clear();
	~The_Maze();
	void printMaze();
	void zeroVisitedArray();
	
};



#endif //MAZERUNNER_CLASS_H
