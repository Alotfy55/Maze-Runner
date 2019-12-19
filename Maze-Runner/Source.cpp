#include "classes.h"

using namespace std;

int main() {

	The_Maze Maze;
	bool found = true;
	cout << "************************************************************************************************************************\n";
	cout << "                                                   Welcome to MazeRunner                                                \n"; 
	cout << "************************************************************************************************************************";
	while (true) {
		int choice;
		char choice2;
		cout << "\nEnter 1 to choose a constructed Maze.\n";
		cout << "Enter 2 to Generate a Maze.\n";
		cout << "Enter 3 to Exit.\n";
		cout << "_____________________________________\nEnter here : ";
		cin >> choice;
		if (choice == 1) {
			string Mazename;
			cout << "Enter the file's name : ";
			cin >> Mazename;
			found = Maze.takeInput(Mazename);
		}
		else if (choice == 2) {
			Maze.GenerateMaze();
		}
		else if (choice == 3)
			break;
		if (found == true) {
			Maze.printMaze();
			Maze.BestFirst();
			Maze.BFS();
			Maze.dfs();
			Maze.DijkstraSearch();
			if (choice == 2) {
				cout << "Do you want to save the Maze? (Y/N) : ";
				cin >> choice2;
				if (choice2 == 'y' || choice2 == 'Y') {
					Maze.saveMazetoFile();
				}
			}
		}
	}
	return 0;
}
