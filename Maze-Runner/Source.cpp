#include "classes.h"

using namespace std;

int main() {

	The_Maze Maze;
	cout << "Welcome to MazeRunner\n"; 
	while (true) {
		int choice;  
		cout << "Press 1 to choose a maze from the file\n";
		cout << "Press 2 to Generate a Maze\n"; 
		cin >> choice; 
		if (choice == 1) {
			string Mazename; 
			cout << "Enter the file name : "; 
			cin >> Mazename; 
			Maze.takeInput(Mazename); 
		}
		else if (choice == 2) {
			Maze.GenerateMaze(); 
		}
		Maze.printMaze();
		Maze.BestFirst();
		Maze.BFS();
		Maze.dfs(); 
		Maze.DijkstraSearch();
		cout << "Press 3 if you want to save the maze or else to proceed\n"; 
		cin >> choice; 
		if (choice == 3) {
			Maze.saveMazetoFile(); 
		}
		 
	}
	return 0;
}
