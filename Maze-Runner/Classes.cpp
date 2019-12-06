#include "Classes.h"
using namespace std;

The_Maze::The_Maze()
{
	row = coloumn = 0;
}



The_Maze::~The_Maze()
{
	for (int i = 0; i < row; i++) 
	{
		delete[] Maze[i];
		delete[] visitedPositions[i];
	}
	delete[] Maze;
	delete[] visitedPositions;
}



void The_Maze::takeInput(string name)
{
		ifstream file(name + ".txt");
		file >> coloumn >> row ;
		file.ignore();
		row = row * 2 + 2;
		coloumn = coloumn * 2 + 2;
		creating_2D_arrays();
		for (int i = 0; i < row ; i++) {
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
	Maze = new char* [row];
	visitedPositions = new bool* [row];
	for (int i = 0; i < row; i++) {
		Maze[i] = new char[coloumn];
		visitedPositions[i] = new bool[coloumn];
	}
}

void The_Maze::printMaze()
{
	cout << startingPoint.first << " " << startingPoint.second << endl << endingPoint.first << " " << endingPoint.second << endl; 
	for (int i = 0; i < row - 1 ; i++)
	{
		for (int j = 0; j < coloumn - 1 ; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}

void The_Maze::zeroVisitedArray() {
	memset(visitedPositions, false, sizeof visitedPositions); 

}

