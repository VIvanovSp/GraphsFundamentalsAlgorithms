// CompetitiveInformaticsHomeworkSolutionsData.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {

private:

	int V; // Number of vertices

	vector<vector<int>> adjMatrix; // Adjacency matrix

public:

	Graph(int V)
	{
		this->V = V;

		adjMatrix.resize(V, vector<int>(V, 0));
	}

	void addEdge(int u, int v)
	{
		adjMatrix[u][v] = 1;

		adjMatrix[v][u] = 1; // Since the graph is undirected
	}

	void DFSUtil(int v, vector<bool>& visited)
	{
		visited[v] = true;

		cout << v << " ";

		for (int i = 0; i < V; ++i) 
		{
			if (adjMatrix[v][i] && !visited[i]) 
			{
				DFSUtil(i, visited);
			}
		}
	}

	void DFS(int v)
	{
		vector<bool> visited(V, false);

		DFSUtil(v, visited);
	}

	void BFS(int s)
	{
		vector<bool> visited(V, false);

		queue<int> q;

		visited[s] = true;

		q.push(s);

		while (!q.empty()) 
		{
			s = q.front();

			cout << s << " ";

			q.pop();

			for (int i = 0; i < V; ++i) 
			{
				if (adjMatrix[s][i] && !visited[i]) 
				{
					visited[i] = true;

					q.push(i);
				}
			}
		}
	}

	bool isCyclicUtil(int v, vector<bool>& visited, int parent)
	{
		visited[v] = true;

		for (int i = 0; i < V; ++i)
		{
			// If an adjacent is not visited, then recur for that adjacent
			if (adjMatrix[v][i])
			{
				if (!visited[i])
				{
					if (isCyclicUtil(i, visited, v))
					{
						return true;
					}
				}
				else
				{
					// If an adjacent is visited and not parent of current vertex,
					// then there is a cycle.
					if (i != parent)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool isCyclic()
	{
		vector<bool> visited(V, false);

		for (int u = 0; u < V; u++) {
			if (!visited[u]) // Don't recur for u if already visited
			{
				if (isCyclicUtil(u, visited, -1))
				{
					return true;
				}
			}
		}

		return false;
	}
};

int main()
{
	int n, m;

	cout << "Enter the number of vertices: ";

	cin >> n;

	cout << "Enter the number of edges: ";

	cin >> m;

	Graph g(n);

	for (int i = 0; i < m; i++)
	{
		int u, v;

		cout << "Enter edge " << i + 1 << " (from to): ";

		cin >> u >> v;

		g.addEdge(u, v);
	}

	cout << "\n\n\nDFS starting from vertex 0:\n";

	g.DFS(0);

	cout << "\n\n\nBFS starting from vertex 0:\n";

	g.BFS(0);

	cout << "\n\n\nCycle Detection: ";

	if (g.isCyclic())
	{
		cout << "Graph contains cycle";
	}
	else
	{
		cout << "Graph doesn't contain cycle";
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
