#include "classes.h"

using namespace std;

int main() {

	The_Maze Maze;
	bool found;
	cout << "************************************************************************************************************************\n";
	cout << "                                                   Welcome to MazeRunner                                                \n"; 
	cout << "************************************************************************************************************************";
	while (true) {
		string choice;
		string choice2;
		found = true;
		cout << "\nEnter 1 to choose a constructed Maze.\n";
		cout << "Enter 2 to Generate a Maze.\n";
		cout << "Enter 3 to Exit.\n";
		cout << "_____________________________________\nEnter here : ";
		cin >> choice;
		if (choice[0] == '1') {
			string Mazename;
			cout << "Enter the file's name : ";
			cin >> Mazename;
			found = Maze.takeInput(Mazename);
		}
		else if (choice[0] == '2') {
			Maze.GenerateMaze();
		}
		else if (choice[0] == 3)
			break;
		else continue;
		if (found == true) {
			Maze.printMaze();
			Maze.BestFirst();
			Maze.BFS();
			Maze.dfs();
			Maze.DijkstraSearch();
			if (choice[0] == '2') {
				cout << "Do you want to save the Maze? (Y/N) : ";
				cin >> choice2;
				if (choice2[0] == 'y' || choice2[0] == 'Y') {
					Maze.saveMazetoFile();
				}
				else if (choice2[0] != 'n' || choice2[0] != 'N');
				continue;
			}
		}
	}
	return 0;
}
