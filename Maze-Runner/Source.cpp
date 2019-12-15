#include "classes.h"

using namespace std;

int main() {
	The_Maze maze;
	maze.takeInput("Maze");
	maze.printMaze();
	maze.dfs();
	maze.BestFirst();
	maze.BFS();
	return 0;
}
