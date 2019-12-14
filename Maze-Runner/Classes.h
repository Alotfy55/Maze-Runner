
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

	node()
	{
		x = 0; y = 0;
	}
	node(int posx, int posy)
	{
		x = posx;
		y = posy;
	}
};

class The_Maze {
	int length, width;

	queue<node> Node;
	int x[4]{ 1,-1,0,0 }, y[4]{ 0,0,1,-1 };

	pair <int, int> startingPoint, endingPoint;
	char** Maze;
	bool** visitedPositions;
	pair<int, int>** parents;
	void creating_2D_arrays();
public:
	The_Maze();
	stack<pair<int, int>> s;
	void dfs();
	void dfs_help();
	void takeInput(string);
	~The_Maze();
	void printMaze();
	void zeroVisitedArray();

	void BFS();
	void BFS_Helper(pair<int, pair<int, int>> ** &Cells, node temp, node temp2);
	void BFS_Found(pair<int, pair<int, int>> ** &Cells, node temp, node temp2, int count);
	void BestFirst();
	double BestFact(pair<int, int>);
	void bestTrack(pair<int, int>, int);
	void getChildren(node, priority_queue<pair<double, pair<int, int>>>&);
	void getChild(node, int, int, priority_queue<pair<double, pair<int, int>>>&);
	void bestTrack(node);
};



#endif //MAZERUNNER_CLASS_H