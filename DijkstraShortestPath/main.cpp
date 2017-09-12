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

class Neighbour
{
public:
	Neighbour(int tail, int weight) : v{tail}, w{weight} { }
	vertex_t tail() const { return v; }
	weight_t weight() const { return w; }
	void print() const { cout << v << "," << w; }
private:
	vertex_t v;
	weight_t w;
};

typedef vector< vector<Neighbour> > graph;
double inf = numeric_limits<double>::max();

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

		vector<Neighbour> adj;

		vertex_t w = 0;
		weight_t weight = 0;
		while (ss >> w)
		{
			--w;

			if (ss.peek() == ',') ss.ignore();
			ss >> weight;

			adj.emplace_back(w, weight);
		}

		G.push_back(adj);
	}

	return G;
}

void printGraph(const graph& G)
{
	for (size_t i = 0; i != G.size(); ++i)
	{
		cout << i << ": ";
		for (const auto& j : G[i])
		{
			j.print();
			cout << " ";
		}
		cout << endl;
	}
}

void printVec(const vector<double>& dist)
{
	for (const auto& i : dist)
		cout << i << " ";
	cout << endl;
}

void dijkstra(const graph& G, int s, vector<double>& dist)
{
	size_t n = G.size();

	// Insert s into x
	set<vertex_t> x;
	x.insert(s);

	// Initialize distance from s to every vertex except itself as inf
	dist.clear();
	dist.resize(n);
	for (auto& i : dist)
		i = inf;
	dist[s] = 0;

	// Main while loop
	while (x.size() < n)
	{
		/* 
		 * For every vertex v in x find an adjacent vertex w which  
		 * is not in x and whose dijkstra's score is minimum
		 */
		
		double min_score = inf;
		vertex_t w = -1;

		for (auto iter = x.begin(); iter != x.end(); ++iter)
		{
			vertex_t v = *iter;
			for (const auto& i : G[v])
			{
				if (x.find(i.tail()) == x.end())
				{
					double score = dist[v] + i.weight();
					if (score <= min_score)
					{
						w = i.tail();
						min_score = score;
					}
				}
			}
		}

		dist[w] = min_score;
		x.insert(w);
	}
}

int main()
{
	graph g = getInput("test.txt");
	printGraph(g);

	vector<double> dist(g.size());
	dijkstra(g, 0, dist);

	printVec(dist);

	return 0;
}
