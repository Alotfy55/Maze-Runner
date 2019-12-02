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
	for (int i = 0; i < length; i++) {
		Maze[i] = new char[width];
		visitedPositions[i] = new bool[width];
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

