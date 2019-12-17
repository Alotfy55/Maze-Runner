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
		delete[] parents[i];
	}
	delete[] parents;
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


//// allocating the dynamic arrays 
void The_Maze::creating_2D_arrays()
{
	Maze = new char*[row];
	parents = new pair<int, int>*[row];
	visitedPositions = new bool*[row];
	for (int i = 0; i < row; i++) {
		Maze[i] = new char[coloumn];
		visitedPositions[i] = new bool[coloumn];
		parents[i] = new pair<int, int>[coloumn];
	}
}



void The_Maze::printMaze()
{
	for (int i = 0; i < row - 1; i++)
	{
		for (int j = 0; j < coloumn - 1; j++)
		{
			cout << Maze[i][j];
		}
		cout << endl;
	}
}


//// initializing all the visited array with zeros 
void The_Maze::zeroVisitedArray() {

	for (int i = 1; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			visitedPositions[i][j] = 0;
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
	coloumn = coloumn * 2 + 2;
	creating_2D_arrays();
	zeroVisitedArray();
	fillMaze();
	Generation();
	CustomizeShapeOfMaze();
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
	startingPoint = { 1,1 };
	endingPoint = { row - 3 , coloumn - 3 };
}


//// Returns a random neighbour to a certain node 
pair < int, int > The_Maze::GetRandomNeighbour(int i, int j) {
	vector <pair < int, int >> allNeighbours;
	int dx[] = { 0 , 0 ,  2 , -2 };
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


//// Returns true if the random neighbours is within the boundaries of the maze 
bool The_Maze::isValid(int i, int j) {
	return i >= 1 && j >= 1 && i < row - 1 && j < coloumn - 1;
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
		for (int i = min(node2.first, node1.first); i <= max(node1.first, node2.first); i++) {
			Maze[i][node1.second] = ' ';
		}
	}
}


//// Fill all the maze with walls 
void The_Maze::fillMaze()
{
	for (int i = 0; i < row - 1; i++) {
		for (int j = 0; j < coloumn - 1; j++) {
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
			if (j == coloumn - 2) {		// last coloumn 
				if (i & 1) {
					Maze[i][j] = '|';
				}
				else {
					Maze[i][j] = '+';
				}
			}
			if (isValid(i, j)) {			// The rest 
				if (i % 2 == 0 && j % 2 == 0) {
					if (Maze[i][j] == '#') {
						Maze[i][j] = '+';
					}
				}
				if ((i & 1) && Maze[i][j] == '#') {
					if (Maze[i - 1][j] != ' ') {
						Maze[i][j] = '|';
					}
				}

			}

		}
	}
	for (int i = 0; i < row - 1; i++) {		// adding the last element '-'
		for (int j = 0; j < coloumn - 1; j++) {
			if (Maze[i][j] == '#') {
				Maze[i][j] = '-';
			}
		}
	}
}

double The_Maze::BestFact(pair<int, int> point)
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

	parents[startingPoint.first][startingPoint.second] = { -1 , -1 };

	int i = 0;
	while (!searchQueue.empty())
	{
		i++;
		pair<double, pair <int, int>> x = searchQueue.top();
		searchQueue.pop();

		if (x.second == endingPoint)
		{
			pair<int, int>* path = new pair<int, int>[i + 1];
			int length = bestTrack(x.second, 0, path);
			printMethod(length, i, path, "Best First Search");
			return;
		}

		node point(x.second.first, x.second.second);
		getChildren(point, searchQueue);

	}
}

int The_Maze::bestTrack(pair<int, int> point, int count, pair<int, int> path[])
{
	pair<int, int> base = { -1,-1 };
	if (parents[point.first][point.second] == base)
	{
		path[count] = point;
		return count;
	}
	int x = bestTrack(parents[point.first][point.second], count + 1, path);
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
	int count = 1;
	while (!Node.empty()) {
		Node.pop();
	}
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
		z++;
		BackTrack[z].first = Cells[temp.x][temp.y].second.first;
		BackTrack[z].second = Cells[temp.x][temp.y].second.second;
		xAxis = temp.x;
		temp.x = Cells[temp.x][temp.y].second.first;
		temp.y = Cells[xAxis][temp.y].second.second;
		
	}

	pair<int, int> *BackTrack2 = new pair<int, int>[z / 2 + 1];
	int iterator = z / 2;
	for (int j = z; j >= 0; j = j - 2)
	{
		if (j != z) {
			BackTrack2[iterator] = BackTrack[j];
		}
		iterator--;
	}

	printMethod(z / 2, count / 2, BackTrack2, "Breadth First Search");
	delete []BackTrack;
	delete []BackTrack2;
	for (int i = 0; i < row; i++)
	{
		delete []Cells[i];
	}
}
void The_Maze::dfs()
{
	dfs_path_ctr = 0;
	dfs_steps_ctr = 0;
	zeroVisitedArray();
	dfs_help(startingPoint.first, startingPoint.second);
	pair<int, int>* path = new pair<int, int>[s.size() + 1];
	int i = s.size()-1;

	while (s.empty() != true)
	{

		path[i].first = s.top().first;
		path[i].second = s.top().second;
		s.pop();
		i--;
	}
	printMethod(dfs_path_ctr, dfs_steps_ctr, path, "Depth First Search");
	delete path;
}


bool The_Maze::dfs_help(int i, int j)
{
	visitedPositions[i][j] = true;
	pair<int, int>temp;
	temp.first = i;
	temp.second = j;
	if (Maze[i][j] == 'E')
	{
		dfs_steps_ctr++;
		s.push(temp);
		//dfs_path_ctr++;
		return true;
	}
	if (Maze[i + 1][j] == ' '&&visitedPositions[i + 2][j] != true)
	{

		visitedPositions[i + 2][j] = true;
		dfs_steps_ctr++;
		if (dfs_help(i + 2, j))
		{
			dfs_path_ctr++;

			s.push(temp);
			return true;
		}
	}
	if (Maze[i][j + 1] == ' '&&visitedPositions[i][j + 2] != true)
	{
		visitedPositions[i][j + 2] = true;
		dfs_steps_ctr++;
		if (dfs_help(i, j + 2))
		{
			dfs_path_ctr++;
			s.push(temp);
			return true;
		}
	}
	if (Maze[i][j - 1] == ' '&&visitedPositions[i][j - 2] != true)
	{
		visitedPositions[i][j - 2] = true;
		dfs_steps_ctr++;
		if (dfs_help(i, j - 2))
		{
			dfs_path_ctr++;
			s.push(temp);
			return true;
		}
	}
	if (Maze[i - 1][j] == ' '&&visitedPositions[i - 2][j] != true)
	{

		visitedPositions[i - 2][j] = true;
		dfs_steps_ctr++;
		if (dfs_help(i - 2, j))
		{
			dfs_path_ctr++;

			s.push(temp);
			return true;
		}
	}
	return false;
}

void The_Maze::printMethod(int length, int visited, pair<int, int>path[], string method)
{
	cout << "Using " << method << " : ";
	cout << "Path Length :" << length << endl << endl;
	for (int i = length; i >= 0; i--)
	{
		cout << "(" << (path[i].second) / 2 << "," << (path[i].first) / 2 << ")" << " ";
	}
	cout << endl << endl << "Total visited Cells :" << visited << endl;
	cout << endl << "***********************************************************************************************************************\n\n" << endl;
}

float The_Maze::calcWeight(vertix c)
{
	return sqrt(pow(endingPoint.first - c.x, 2) + pow(endingPoint.second - c.y, 2));
}
unordered_set<int>Visited;
void The_Maze::addEdge(vector<pair<vertix, vector<pair<float, vertix>>>> & Nodes, vertix S)
{
	if (Maze[S.x + 1][S.y] == ' ')
	{
		float w = calcWeight(Nodes[S.num + ((coloumn - 1) / 2)].first);
		vertix E = Nodes[S.num + ((coloumn - 1) / 2)].first;
		if (Visited.find(E.num) == Visited.end())
		{
			Nodes[S.num].second.push_back(make_pair(w, E));
			Nodes[E.num].second.push_back(make_pair(w, S));
			Visited.insert(S.num);
			addEdge(Nodes, E);
		}
	}
	if (Maze[S.x - 1][S.y] == ' ')
	{
		float w = calcWeight(Nodes[S.num - ((coloumn - 1) / 2)].first);
		vertix E = Nodes[S.num - ((coloumn - 1) / 2)].first;
		if (Visited.find(E.num) == Visited.end())
		{
			Nodes[S.num].second.push_back(make_pair(w, E));
			Nodes[E.num].second.push_back(make_pair(w, S));
			Visited.insert(S.num);
			addEdge(Nodes, E);
		}
	}
	if (Maze[S.x][S.y + 1] == ' ')
	{
		float w = calcWeight(Nodes[S.num + 1].first);
		vertix E = Nodes[S.num + 1].first;
		if (Visited.find(E.num) == Visited.end())
		{
			Nodes[S.num].second.push_back(make_pair(w, E));
			Nodes[E.num].second.push_back(make_pair(w, S));
			Visited.insert(S.num);
			addEdge(Nodes, E);
		}
	}
	if (Maze[S.x][S.y - 1] == ' ')
	{
		float w = calcWeight(Nodes[S.num - 1].first);
		vertix E = Nodes[S.num - 1].first;
		if (Visited.find(E.num) == Visited.end())
		{
			Nodes[S.num].second.push_back(make_pair(w, E));
			Nodes[E.num].second.push_back(make_pair(w, S));
			Visited.insert(S.num);
			addEdge(Nodes, E);
		}

	}
	else
		return;



	//Nodes[sNum].second.push_back(make_pair(15,Nodes[eNum].first));
}
int startNode;
int endNode;
void The_Maze::DijkstraSearch()
{
	int N = ((coloumn - 1) / 2)*((row - 1) / 2);
	vector<pair<vertix, vector<pair<float, vertix>>>> Nodes(N);
	int k = 0;
	while (k < N)
	{
		for (int i = 1; i < row - 1; i += 2)
		{
			for (int j = 1; j < coloumn - 1; j += 2)
			{
				if (i == startingPoint.first && j == startingPoint.second)
				{
					Nodes[k].first.x = i;
					Nodes[k].first.y = j;
					Nodes[k].first.num = k;
					Nodes[k].first.cost = 0;
					Nodes[k].first.parent = 0;
					startNode = k;
				}
				else
				{
					Nodes[k].first.x = i;
					Nodes[k].first.y = j;
					Nodes[k].first.num = k;
					Nodes[k].first.cost = INFINITY;
				}
				if (i == endingPoint.first&&j == endingPoint.second)
					endNode = k;

				k++;
			}
		}

	}
	vertix s = Nodes[startNode].first;
	addEdge(Nodes, s);
	vector<pair<float, vertix>>::iterator it;
	Dijkstra(Nodes);
}
void The_Maze::Dijkstra(vector<pair<vertix, vector<pair<float, vertix>>>> & Nodes)
{
	typedef pair<float, vertix*> pr;
	priority_queue<pr, vector<pr>, greater<pr>> pq;
	unordered_set<int> VisitedNodes;
	vertix* temp = NULL;
	float c;
	int N = ((coloumn - 1) / 2)*((row - 1) / 2);
	for (int i = 0; i < N; i++)
	{
		temp = &Nodes[i].first;
		c = temp->cost;
		pq.push(make_pair(c, temp));
	}
	vertix* s = NULL;
	while (pq.empty() == false)
	{
		s = pq.top().second;
		pq.pop();
		vector<pair<float, vertix>>::iterator it;
		for (it = Nodes[s->num].second.begin(); it != Nodes[s->num].second.end(); it++)
		{
			if (VisitedNodes.find(it->second.num) == VisitedNodes.end())
			{
				if (it->first + s->cost < it->second.cost)
				{
					Nodes[it->second.num].first.cost = it->first + s->cost;
					Nodes[it->second.num].first.parent = s->num;
					pq.push(make_pair(Nodes[it->second.num].first.cost, &Nodes[it->second.num].first));
				}
			}
		}
		VisitedNodes.insert(s->num);
	}
	showOut(Nodes);
}
void The_Maze::showOut(vector<pair<vertix, vector<pair<float, vertix>>>> & Nodes)
{
	stack<pair<int, int>>out;
	vertix par = Nodes[endNode].first;
	while (par.num != startNode)
	{
		out.push(make_pair(par.x, par.y));
		par = Nodes[par.parent].first;
	}
	par = Nodes[startNode].first;
	out.push(make_pair(par.x, par.y));
	int size = out.size(); //Number of Moves
	pair<int, int>* thePath = new pair<int, int>[size]; //El array elly shayel el path
	int ind = size - 1;
	while (out.empty() == false || ind > 0)
	{
		thePath[ind].first = out.top().first;
		thePath[ind].second = out.top().second;
		//Maze[out.top().first][out.top().second]='*' //hna b3'yr fe el maze nfsaha
		out.pop();
		ind--;
	}
	printMethod(size-1, size , thePath, "Dijkstra");
}