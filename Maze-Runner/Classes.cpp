#include "Classes.h"
#include<string>
#include <limits>
#include<iostream>
#include<cmath>
#include<unordered_set>
#include<queue>
#include<stack>
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
	for (int i = 0; i < length; i++) {
		Maze[i] = new char[width];
		visitedPositions[i] = new bool[width];
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

float The_Maze::calcWeight(vertix c)
{
	return sqrt(pow(endingPoint.first - c.x, 2) + pow(endingPoint.second - c.y, 2));
}
unordered_set<int>Visited;
void The_Maze::addEdge(vector<pair<vertix, vector<pair<float, vertix>>>> & Nodes, vertix S)
{
	if (Maze[S.x + 1][S.y] == ' ')
	{
		float w = calcWeight(Nodes[S.num + ((length - 1) / 2)].first);
		vertix E = Nodes[S.num + ((length - 1) / 2)].first;
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
		float w = calcWeight(Nodes[S.num - ((length - 1) / 2)].first);
		vertix E = Nodes[S.num - ((length - 1) / 2)].first;
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
void The_Maze::makeGraph()
{
	int N = ((length - 1) / 2)*((width - 1) / 2);
	vector<pair<vertix, vector<pair<float, vertix>>>> Nodes(N);
	int k = 0;
	while (k < N)
	{
		for (int i = 1; i < width - 1; i += 2)
		{
			for (int j = 1; j < length - 1; j += 2)
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
	int N = ((length - 1) / 2)*((width - 1) / 2);
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
	while (par.num!=startNode)
	{
		out.push(make_pair(par.x, par.y));
		par = Nodes[par.parent].first;
	}
	par= Nodes[startNode].first;
	out.push(make_pair(par.x, par.y));
	int i, j;
	while (out.empty() == false)
	{
		i = out.top().first;
		j = out.top().second;
		Maze[i][j] = '*';
		out.pop();
	}
	printMaze();
}


