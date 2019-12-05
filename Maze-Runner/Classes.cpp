#include "Classes.h"
using namespace std;

The_Maze::The_Maze()
{
	length = width = 0;
}



The_Maze::~The_Maze()
{
	/*for (int i = 0; i < length; i++) 
	{
		delete[] Maze[i];
		delete[] visitedPositions[i];
	}*/
	delete[] Maze;
	delete[] visitedPositions;
}



void The_Maze::takeInput(string name)
{
		ifstream file(name + ".txt");
		file >> length >> width;
		file.ignore();
		length = length * 2 + 2;
		width = width * 2 + 2;
		creating_2D_arrays();
		for (int i = 0; i < width; i++) {
			string maze;
			getline(file, maze);
			for (int j = 0; j < maze.length(); j++) {
				Maze[i][j] = maze[j];
				if (Maze[i][j] == 'S') {
					startingPoint = { i, j };
				}
				if (Maze[i][j] == 'E') {
					endingPoint = { i, j };
				}
			}
		}
}


void The_Maze::creating_2D_arrays()
{
	Maze = new char* [length];
	visitedPositions = new bool* [length];
	parents = new pair<int, int>*[length];
	for (int i = 0; i < length; i++) {
		Maze[i] = new char[width];
		visitedPositions[i] = new bool[width];
		parents[i] = new pair<int, int>[width];
	}
}

void The_Maze::printMaze()
{
	for (int i = 0; i < width-1; i++)
	{
		for (int j = 0; j < length-1; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}

void The_Maze::zeroVisitedArray() {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			visitedPositions[i][j] = false;
		}
	}

}

double The_Maze::BestFact(pair<int,int> point)
{
	double fact = sqrt(pow((endingPoint.first - point.first), 2) + pow((endingPoint.second - point.second), 2));
	return fact;
}

void The_Maze::BestFirst() {
	zeroVisitedArray();

	priority_queue<pair<double, pair<int, int>>> searchQueue;
	pair<double, pair<int, int>> start;
	start.first = -1;
	start.second = startingPoint;
	visitedPositions[startingPoint.first][startingPoint.second] = true;
	searchQueue.push(start);
	parents[startingPoint.first][startingPoint.second] = {-1 , -1};
	int i = 0;
	while (!searchQueue.empty())
	{
		pair<double, pair <int, int>> x = searchQueue.top();
		searchQueue.pop();
		if (x.second == endingPoint)
		{
			cout << "found at :: " << (x.second.second) / 2 << " " << (x.second.first) / 2 << endl ;
			bestTrack(x.second , 0);
			return;
		}
		node point(x.second.first, x.second.second, 0);
		getChildren(point, searchQueue);
		
	}
}

void The_Maze::bestTrack(pair<int, int> point , int count)
{
	pair<int, int> base = { -1,-1 };
	if (parents[point.first][point.second] == base)
	{
		cout << "Path is " << count << " steps long" << endl;
		cout << "(" << (point.first)/2 << "," << (point.second)/2 << ")" << " ";
		return;
	}
	bestTrack(parents[point.first][point.second], count + 1);
	cout << "(" << (point.second) / 2 << "," << (point.first) / 2 << ")" << " ";
	return;
}

void The_Maze::getChildren(node point, priority_queue<pair<double, pair<int, int>>>& searchingQueue) {
	// upper cell
	getChild(point, 0, -1, searchingQueue);
	//lower cell
	getChild(point, 0, 1, searchingQueue);
	//right cell
	getChild(point, 1, 0, searchingQueue);
	//left cell
	getChild(point, -1, 0, searchingQueue);
}

void The_Maze::getChild(node point, int x, int y, priority_queue<pair<double, pair<int, int>>>& searchingQueue) {
	if (Maze[point.x + x][point.y + y] == ' ' && !visitedPositions[point.x + (x * 2)][point.y + (y * 2)])
	{
		visitedPositions[point.x + (x * 2)][point.y + (y * 2)] = true;

		pair<int, int> newPoint;
		newPoint.first = point.x + (x * 2);
		newPoint.second = point.y + (y * 2);

		double DistToEnd = BestFact(newPoint);

		parents[newPoint.first][newPoint.second] = { point.x , point.y };

		pair<double, pair<int, int>> append;
		append.first = DistToEnd;
		append.second = newPoint;

		searchingQueue.push(append);
	}
}