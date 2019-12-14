#include "classes.h"

using namespace std;

int main() {
	The_Maze maze;
	maze.takeInput("Maze");
	maze.printMaze();

	maze.BestFirst();

	maze.BFS();

	maze.dfs();
	system("pause");
	return 0;
}
