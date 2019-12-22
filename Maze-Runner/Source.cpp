#include "classes.h"

using namespace std;

void search(The_Maze Maze);

int main() {

	The_Maze Maze;
	bool found;

	while (true) {
		cout << "************************************************************************************************************************\n";
		cout << "                                                   Welcome to MazeRunner                                                \n";
		cout << "************************************************************************************************************************";
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
		else if (choice[0] == '3')
			break;
		else {
			system("cls");
			continue;
		}
		if (found == true) {
			Maze.MazeSave();
			Maze.printMaze();
			cout << "Do You want to solve the maze Using Searching Algorithms or Your brain? " << endl << endl;
			cout << "1)Brain \n2)Computer Algorithms \nThe Choice is yours: ";
			cin >> choice2;
			if (choice2[0] == '1')
			{
				Maze.game();
				cout << "Do you want to compare yourself with Computer Algorithms (Y/N) : ";
				cin >> choice2;
				cout << "\n************************************************************************************************************************\n";
				if (choice2[0] == 'y' || choice2[0] == 'Y') {
					search(Maze);
				}
				else {
					system("cls");
					continue;
				}
			}
			else if (choice2[0] == '2')
			{
				search(Maze);
			}
			else {
				system("cls");
				continue;
			}
			if (choice[0] == '2') {
				cout << "Do you want to save the Maze? (Y/N) : ";
				cin >> choice2;
				if (choice2[0] == 'y' || choice2[0] == 'Y') {
					Maze.saveMazetoFile();
				}

			}
		}
		system("cls");
	}
	return 0;
}

void search(The_Maze Maze)
{
	Maze.BestFirst();
	cout << "Press any key to Continue!";
	_getch();
	printf("\r                                      ");
	Maze.BFS();
	cout << "Press any key to Continue!";
	_getch();
	printf("\r                                      ");
	Maze.dfs();
	cout << "Press any key to Continue!";
	_getch();
	printf("\r                                      ");
	Maze.DijkstraSearch();
	cout << "Press any key to Continue!";
	_getch();
	printf("\r                                      ");
	cout << "\n\nThe Shortest Path is.";
	Maze.printMaze();
}