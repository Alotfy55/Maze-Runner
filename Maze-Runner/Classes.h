
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
	pair <int, int> startingPoint, endingPoint;
	char** Maze;
	bool** visitedPositions;
	pair<int, int>** parents;
	void creating_2D_arrays();
	stack<pair<int, int>> s;
	int dfs_path_ctr = 0;
	int dfs_steps_ctr = 0;
public:
	The_Maze();
	void takeInput(string);
	~The_Maze();
	void printMaze();
	void zeroVisitedArray();
	void BFS();
	void BestFirst();
	double BestFact(pair<int, int>);
	void bestTrack(pair<int, int>, int);
	void getChildren(node, priority_queue<pair<double, pair<int, int>>>&);
	void getChild(node, int, int, priority_queue<pair<double, pair<int, int>>>&);
	void bestTrack(node);
	bool dfs_help(int i , int j);
	void dfs();
};



#endif //MAZERUNNER_CLASS_H
