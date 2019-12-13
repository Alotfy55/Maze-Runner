#include "Classes.h"
using namespace std;

The_Maze::The_Maze()
{
	row = coloumn = 0;
}



The_Maze::~The_Maze()
{
	clear(); 
}


//// deallocate the dynamic array used
void The_Maze::clear() {
	for (int i = 0; i < row; i++)
	{
		delete[] Maze[i];
		delete[] visitedPositions[i];
	}
	delete[] Maze;
	delete[] visitedPositions;
}



//// take the name of the txt file then load it into the 2d maze 
void The_Maze::takeInput(string name)
{
		ifstream file(name + ".txt");
		if (!file.is_open()) {
			cout << "Invalid file name\n"; 
			return; 
		}
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


//// allocating the dymaic arrays 
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
	for (int i = 0; i < row - 1 ; i++)
	{
		for (int j = 0; j < coloumn - 1 ; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}


//// intializing all the visited array with zeros 
void The_Maze::zeroVisitedArray() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < coloumn; j++) {
			visitedPositions[i][j] = false; 
		}
	}
}




void The_Maze::GenerateMaze() 
{
	
	cout << "Please enter the length : "; 
	cin >> row; 
	cout << "and the width : "; 
	cin >> coloumn; 
	row = row * 2 + 2; 
	coloumn = coloumn * 2  + 2; 
	creating_2D_arrays(); 
	zeroVisitedArray();
	fillMaze(); 
	Generation(); 
	CustomizeShapeOfMaze() ;
	
}


//// Generation of the maze using dfs starting from ( 1 , 1 ) 
void The_Maze::Generation() {
	stack <pair< int, int >> Nodes; 
	Nodes.push({ 1,1 }); 
	visitedPositions[1][1] = 1; 
	while (!Nodes.empty()) { 
		pair < int, int > curNode = Nodes.top(); 
		pair < int, int > nextNode = GetRandomNeighbour(curNode.first, curNode.second);
		if (nextNode.first == -1) {
			Nodes.pop(); 
		}
		else {
			visitedPositions[nextNode.first][nextNode.second] = 1; 
			Nodes.push(nextNode);
			ConnectTwoNodes(curNode, nextNode); 
		}
	}
	Maze[1][1] = 'S'; 
	Maze[row - 3][coloumn - 3] = 'E'; 
}


//// Returns a random neighbour to a certain node 
pair < int , int > The_Maze::GetRandomNeighbour(int i , int j ) {
	vector <pair < int, int >> allNeighbours; 
	int dx[] = { 0 , 0 ,  2 , -2}; 
	int dy[] = { 2 , -2 , 0 , 0 };
	for (int k = 0; k < 4; k++) {
		int xc = dx[k] + i, xy = dy[k] + j; 
		if (isValid(xc, xy) && !visitedPositions[xc][xy]) {
			allNeighbours.push_back({ xc,xy }); 
		}
	}
	if (allNeighbours.size() == 0)
	{
		allNeighbours.push_back({ -1,-1 });
		return allNeighbours[0]; 
	}
	int random = rand() % allNeighbours.size(); 
	return allNeighbours[random]; 
}


//// Returns true if the random neighbours is within the boundries of the maze 
bool The_Maze::isValid(int i, int j) {
	return i >= 1 && j >= 1 && i < row-1 && j < coloumn-1; 
}


//// Connect a road between two nodes on the maze 
void The_Maze::ConnectTwoNodes(pair < int, int > node1, pair < int, int > node2) 
{
	if (node1.first == node2.first) {
		for (int i = min(node2.second, node1.second); i <= max(node1.second, node2.second); i++) {
			Maze[node1.first][i] = ' '; 
		}
	}
	else {
		for (int i = min(node2.first, node1.first); i <= max(node1.first , node2.first); i++) {
			Maze[i][node1.second] = ' ';
		}
	}
}


//// Fill all the maze with walls 
void The_Maze::fillMaze() 
{
	for (int i = 0; i < row - 1 ; i++) {
		for (int j = 0; j < coloumn - 1 ; j++) {
			Maze[i][j] = '#'; 
		}
	}
}


//// Change the character of the maze to be like a real maze
void The_Maze::CustomizeShapeOfMaze() {
	for (int i = 0; i < row - 1; i++) {
		for (int j = 0; j < coloumn - 1; j++) {
			if (i == 0) {		// first row 
				if (j & 1) {
					Maze[i][j] = '-'; 
				}
				else {
					Maze[i][j] = '+'; 
				}
			}
			if (i == row - 2) {		//second row
				if (j & 1) {
					Maze[i][j] = '-';
				}
				else {
					Maze[i][j] = '+';
				}
			}
			if (j == 0) {			// first coloumn 
				if (i & 1) {
					Maze[i][j] = '|'; 
				}
				else {
					Maze[i][j] = '+'; 
				}
			}
			if (j == coloumn-2) {		// last coloumn 
				if (i & 1) {
					Maze[i][j] = '|';
				}
				else {
					Maze[i][j] = '+';
				}
			}
			if (isValid(i,j)) {			// The rest 
				if (i % 2 == 0 && j % 2 == 0) {
					if (Maze[i][j] == '#') {
						Maze[i][j] = '+'; 
					}
				}
				if ( (i & 1) && Maze[i][j] == '#') {
					if ( Maze[i-1][j] != ' ' ) {
						Maze[i][j] = '|'; 
					}
				}
				
			}
			
		}
	}
	for (int i = 0; i < row - 1; i++) {		
		for (int j = 0; j < coloumn - 1; j++) {
			if (Maze[i][j] == '#') {
				Maze[i][j] = '-'; 
			}
		}
	}

}

