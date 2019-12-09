#include "classes.h"

using namespace std;

int main() {
	The_Maze maze;
	maze.takeInput("Maze");
	maze.printMaze();
	cout << endl;
	maze.BestFirst();
	cout << endl;
	maze.BFS();
	cout << endl;
	maze.dfs();
	system("pause");
	return 0;
}
