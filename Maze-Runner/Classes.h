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

struct node
{
	int x, y;
	int DistanceToPoint;
	node* parent;
	node()
	{
		x = 0; y = 0; DistanceToPoint = 0; parent = NULL;
	}
	node(int posx, int posy, int Dist)
	{
		x = posx;
		y = posy;
		DistanceToPoint = Dist;
	}
};

class The_Maze {
	int length, width;
	pair <int, int> startingPoint, endingPoint;
	char** Maze;
	bool** visitedPositions;
	pair<int, int>** parents;
	void creating_2D_arrays();
public:
	The_Maze();
	void takeInput(string);
	~The_Maze();
	void printMaze();
	void zeroVisitedArray();

	void BestFirst();
	double BestFact(pair<int,int>);
	void bestTrack(pair<int,int> , int);
	void getChildren(node, priority_queue<pair<double, pair<int, int>>>&);
	void getChild(node, int, int, priority_queue<pair<double, pair<int, int>>>&);
	void bestTrack(node);
};



#endif //MAZERUNNER_CLASS_H
