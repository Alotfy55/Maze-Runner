#include "classes.h"

using namespace std;

int main() {
	The_Maze maze;
	maze.takeInput("Maze");
	maze.printMaze();
	cout << endl << "***************************************************************************************\n\n" << endl;
	maze.BestFirst();
	return 0;
}