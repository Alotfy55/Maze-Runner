#include "classes.h"
#include<string>
using namespace std;

int main() {
	The_Maze maze;
	maze.takeInput("Maze");
	maze.printMaze();
	maze.DijkstraSearch();
	return 0;
}
