#include "Classes.h"
using namespace std;

The_Maze::The_Maze()
{
	length = width = 0;

}



The_Maze::~The_Maze()
{
	/*for (int i = 0; i < length; i++)
	{
		delete[] Maze[i];
		delete[] visitedPositions[i];
	}*/
	delete[] Maze;
	delete[] visitedPositions;
}



void The_Maze::takeInput(string name)
{
	ifstream file(name + ".txt");
	file >> length >> width;
	file.ignore();
	length = length * 2 + 2;
	width = width * 2 + 2;
	creating_2D_arrays();
	for (int i = 0; i < width; i++) {
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
	Maze = new char*[length];
	visitedPositions = new bool*[length];
	parents = new pair<int, int>*[length];
	for (int i = 0; i < length; i++) {
		Maze[i] = new char[width];
		visitedPositions[i] = new bool[width];
		parents[i] = new pair<int, int>[width];
	}
}

void The_Maze::printMaze()
{
	for (int i = 0; i < width - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}

void The_Maze::zeroVisitedArray() {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			visitedPositions[i][j] = false;
		}
	}

}

double The_Maze::BestFact(pair<int, int> point)
{
	double fact = sqrt(pow((endingPoint.first - point.first), 2) + pow((endingPoint.second - point.second), 2));
	return fact;
}

void The_Maze::BestFirst() {
	zeroVisitedArray();

	priority_queue<pair<double, pair<int, int>>> searchQueue;
	pair<double, pair<int, int>> start;
	start.first = -1;
	start.second = startingPoint;
	visitedPositions[startingPoint.first][startingPoint.second] = true;
	searchQueue.push(start);
	parents[startingPoint.first][startingPoint.second] = { -1 , -1 };
	int i = 0;
	while (!searchQueue.empty())
	{
		pair<double, pair <int, int>> x = searchQueue.top();
		searchQueue.pop();
		if (x.second == endingPoint)
		{
			cout << "found at :: " << (x.second.second) / 2 << " " << (x.second.first) / 2 << endl;
			bestTrack(x.second, 0);
			return;
		}
		node point(x.second.first, x.second.second);
		getChildren(point, searchQueue);

	}
}

void The_Maze::bestTrack(pair<int, int> point, int count)
{
	pair<int, int> base = { -1,-1 };
	if (parents[point.first][point.second] == base)
	{
		cout << "Path is " << count << " steps long" << endl;
		cout << "(" << (point.first) / 2 << "," << (point.second) / 2 << ")" << " ";
		return;
	}
	bestTrack(parents[point.first][point.second], count + 1);
	cout << "(" << (point.second) / 2 << "," << (point.first) / 2 << ")" << " ";
	return;
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

	pair<int, pair<int, int>> ** Cells = new pair<int, pair<int, int>>*[length];
	for (int i = 0; i < length; i++)
	{
		Cells[i] = new pair<int, pair<int, int>>[width];
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
