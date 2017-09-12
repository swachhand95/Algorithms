#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

typedef int vertex_t;
typedef double weight_t;

typedef pair<vertex_t, weight_t> neighbor;
typedef vector<vector<neighbor>> graph;
const double INF = numeric_limits<double>::max();

graph getInput(const string& filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
		return graph();

	string line;
	graph G;
	while (getline(fin, line))
	{
		stringstream ss(line);

		vertex_t v = 0;
		ss >> v;
		--v;

		vector<pair<vertex_t, weight_t>> adj;

		vertex_t w = 0;
		weight_t weight = 0;
		while (ss >> w)
		{
			--w;

			if (ss.peek() == ',') ss.ignore();
			ss >> weight;

			adj.push_back(make_pair(w, weight));
		}

		G.push_back(adj);
	}

	return G;
}

void printGraph(const graph& G)
{
	for (int i = 0; i != G.size(); ++i)
	{
		cout << i << ": ";
		for (const auto& j : G[i])
			cout << j.first << "," << j.second << " ";
		cout << endl;
	}
}

void printVec(const vector<weight_t>& dist)
{
	for (const auto& i : dist)
		cout << i << " ";
	cout << endl;
}

void dijkstra(const graph& G, int s, vector<double>& dist)
{
	size_t sz = G.size();

	// Initialize the dist of all vertices except s to INF
	dist.clear();
	dist.resize(sz);
	for (auto& i : dist)
		i = INF;
	dist[s] = 0;

	// Make a set x which will contain all the elements that haven't yet been explored
	set<pair<weight_t, vertex_t>> x;
	for (vertex_t i = 0; i != sz; ++i)
		x.insert(make_pair(dist[i], i));

	while (!x.empty())
	{
		// Extract the vertex v that has the minimum distance from s i.e. extractMin
		vertex_t v = x.begin()->second;
		weight_t len = x.begin()->first;
		dist[v] = len;
		x.erase(x.begin());

		// Update the key of every vertex adjacent to v that is in x
		for (vertex_t i = 0; i != G[v].size(); ++i)
		{
			vertex_t w = G[v][i].first;
			weight_t len_vw = G[v][i].second;

			auto it = x.find(make_pair(dist[w], w));
			if (it != x.end())
			{
				if (it->first > dist[v] + len_vw)
				{
					dist[w] = dist[v] + len_vw;
					x.erase(it);
					x.insert(make_pair(dist[v] + len_vw, w));
				}
			}
		}
	}
}

int main()
{
	graph g = getInput("dijkstraData.txt");
	// printGraph(g);

	vector<double> dist(g.size());
	dijkstra(g, 0, dist);

    cout << dist[6] << " " <<
        dist[36] << " " <<
        dist[58] << " " <<
        dist[81] << " " <<
        dist[98] << " " <<
        dist[114] << " " <<
        dist[132] << " " <<
        dist[164] << " " <<
        dist[187] << " " <<
        dist[196] << " " << endl;
    return 0;
}
