#include "Classes.h"
using namespace std;

The_Maze::The_Maze()
{
	row = coloumn = 0;
}

The_Maze::~The_Maze()
{
	for (int i = 0; i < row; i++)
	{
		delete[] Maze[i];
		delete[] visitedPositions[i];
		delete[] parents[i];
	}
	delete[] parents;
	delete[] Maze;
	delete[] visitedPositions;
}

void The_Maze::takeInput(string name)
{
	ifstream file(name + ".txt");
	file >> coloumn >> row;
	file.ignore();
	row = row * 2 + 2;
	coloumn = coloumn * 2 + 2;
	creating_2D_arrays();
	for (int i = 0; i < row; i++) {
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

void The_Maze::creating_2D_arrays()
{
	Maze = new char* [row];
	parents = new pair<int, int>* [row];

	visitedPositions = new bool* [row];
	for (int i = 0; i < row; i++) {
		Maze[i] = new char[coloumn];
		visitedPositions[i] = new bool[coloumn];
		parents[i] = new pair<int, int>[coloumn];
	}
}

void The_Maze::printMaze()
{

	cout << startingPoint.first << " " << startingPoint.second << endl << endingPoint.first << " " << endingPoint.second << endl;
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < coloumn - 1; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}

void The_Maze::zeroVisitedArray() {
	for (int i = 1; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			visitedPositions[i][j] = 0;
		}
	}
}

double The_Maze::BestFact(pair<int,int> point)
{
	double fact = sqrt(pow((endingPoint.first - point.first), 2) + pow((endingPoint.second - point.second), 2));
	return -fact;
}

void The_Maze::BestFirst() {
	
	zeroVisitedArray();
	priority_queue<pair<double, pair<int, int>>> searchQueue;
	pair<double, pair<int, int>> start;
	
	start.first = 0;
	start.second = startingPoint;
	
	visitedPositions[startingPoint.first][startingPoint.second] = true;
	
	searchQueue.push(start);
	
	parents[startingPoint.first][startingPoint.second] = {-1 , -1};
	
	int i = 0;
	while (!searchQueue.empty())
	{
		i++;
		pair<double, pair <int, int>> x = searchQueue.top();
		searchQueue.pop();
	
		if (x.second == endingPoint)
		{
			pair<int, int>* path = new pair<int, int>[i+1];
			int length = bestTrack(x.second , 0 , path);
			printMethod(length, i, path, "Best First Search");
			return;
		}
		
		node point(x.second.first, x.second.second);
		getChildren(point, searchQueue);
		
	}
}

int The_Maze::bestTrack(pair<int, int> point , int count , pair<int, int> path [])
{
	pair<int, int> base = { -1,-1 };
	if (parents[point.first][point.second] == base)
	{
		path[count] = point; 
		return count;
	}
	int x = bestTrack(parents[point.first][point.second], count + 1 , path);
	path[count] = point;
	return x;
}

void The_Maze::getChildren(node point, priority_queue<pair<double, pair<int, int>>>& searchingQueue) {
	// upper cell
	getChild(point, 0, -1, searchingQueue);
	//lower cell
	getChild(point, 0, 1, searchingQueue);
	//right cell
	getChild(point, 1, 0, searchingQueue);
	//left cell
	getChild(point, -1, 0, searchingQueue);
}

void The_Maze::getChild(node point, int x, int y, priority_queue<pair<double, pair<int, int>>>& searchingQueue) {
	if (Maze[point.x + x][point.y + y] == ' ' && !visitedPositions[point.x + (x * 2)][point.y + (y * 2)])
	{
		visitedPositions[point.x + (x * 2)][point.y + (y * 2)] = true;


		pair<int, int> newPoint;
		newPoint.first = point.x + (x * 2);
		newPoint.second = point.y + (y * 2);

		double DistToEnd = BestFact(newPoint);

		parents[newPoint.first][newPoint.second] = { point.x , point.y };

		pair<double, pair<int, int>> append;
		append.first = DistToEnd;
		append.second = newPoint;

		searchingQueue.push(append);
	}
}

void The_Maze::BFS()
{
	zeroVisitedArray();
	int count = 0;

	pair<int, pair<int, int>> ** Cells = new pair<int, pair<int, int>>*[row];
	for (int i = 0; i < row; i++)
	{
		Cells[i] = new pair<int, pair<int, int>>[coloumn];
	}

	node temp(startingPoint.first, startingPoint.second), temp2(0, 0);

	Node.push(temp);
	visitedPositions[temp.x][temp.y] = true;

	Cells[temp.x][temp.y].first = 0;
	Cells[temp.x][temp.y].second.first = -1;
	Cells[temp.x][temp.y].second.second = -1;

	while (!Node.empty())
	{
		temp = Node.front();
		Node.pop();
		visitedPositions[temp.x][temp.y] = true;

		if (temp.x == endingPoint.first && temp.y == endingPoint.second)
		{
			BFS_Found(Cells, temp, temp2, count);
			break;
		}
		else {
			BFS_Helper(Cells, temp, temp2);
		}
		count++;
	}
}

void The_Maze::BFS_Helper(pair<int, pair<int, int>> ** &Cells, node temp, node temp2) //Checks Neighbouring cells.
{
	int x[4]{ 1,-1,0,0 }, y[4]{ 0,0,1,-1 };
	for (int i = 0; i < 4; i++) {
		if ((Maze[temp.x + x[i]][temp.y + y[i]] == ' ' || Maze[temp.x + x[i]][temp.y + y[i]] == 'E') &&
			visitedPositions[temp.x + x[i]][temp.y + y[i]] == 0)
		{
			Cells[temp.x + x[i]][temp.y + y[i]].first = Cells[temp.x][temp.y].first + 1;
			Cells[temp.x + x[i]][temp.y + y[i]].second.first = temp.x;
			Cells[temp.x + x[i]][temp.y + y[i]].second.second = temp.y;
			temp2 = temp;
			temp2.x += x[i];
			temp2.y += y[i];
			Node.push(temp2);
		}
	}
}
void The_Maze::BFS_Found(pair<int, pair<int, int>> ** &Cells, node temp, node temp2, int count)
{
	int z = 0, xAxis;
	pair<int, int> *BackTrack = new pair<int, int>[count];
	visitedPositions[temp.x][temp.y] = true;

	BackTrack[0].first = temp.x;
	BackTrack[0].second = temp.y;
	while (Cells[temp.x][temp.y].second.first != -1)
	{
		BackTrack[z].first = Cells[temp.x][temp.y].second.first;
		BackTrack[z].second = Cells[temp.x][temp.y].second.second;
		xAxis = temp.x;
		temp.x = Cells[temp.x][temp.y].second.first;
		temp.y = Cells[xAxis][temp.y].second.second;
		z++;
	}

	pair<int, int> *BackTrack2 = new pair<int, int>[z / 2 + 1];
	int iterator = z / 2;
	for (int j = z; j >= 0; j = j - 2)
	{

		BackTrack2[iterator] = BackTrack[j];
		iterator--;
	}

	printMethod(z / 2, count / 2, BackTrack2, "Breadth First Search");

}

void The_Maze::printMethod(int length, int visited, pair<int, int>path[] , string method)
{
	cout << "Using " << method << " : ";
	cout << "Path Length :" << length << endl << endl;
	for (int i = length ; i >= 0 ;  i--)
	{
		cout << "(" << (path[i].second) / 2 << "," << (path[i].first) / 2 << ")" << " ";
	}
	cout << endl << endl << "Total visited Cells :" << visited << endl;
	cout << endl << "***********************************************************************************************************************\n\n" << endl;
}
