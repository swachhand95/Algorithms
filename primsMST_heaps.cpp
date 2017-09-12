#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

typedef long long int vertex_t;
typedef long long int weight_t;
typedef pair<vertex_t, weight_t> neighbor;
typedef vector< vector<neighbor> > graph;
weight_t inf = numeric_limits<weight_t>::max();

void addEdge(graph &G, vertex_t u, vertex_t v, weight_t w)
{
    if (u < G.size() && v < G.size() && u != v)
    {
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }
}

graph createGraph(const string &filename)
{
    ifstream fin(filename.c_str());
    if (!fin.is_open())
        return graph();

    long long int n = 0, m = 0;
    fin >> n >> m;

    graph G(n);

    while (m--)
    {
        vertex_t u = 0, v = 0;
        weight_t w = 0;
        fin >> u >> v >> w;
        
        addEdge(G, u - 1, v - 1, w);
    }

    return G;
}

void printGraph(const graph &G)
{
    for (vertex_t u = 0; u < G.size(); ++u)
    {
        cout << u << ": ";
        for (size_t i = 0; i < G[u].size(); ++i)
            cout << G[u][i].first << "," << G[u][i].second << " ";
        cout << endl;
    }
}

graph primsMST(graph &G, weight_t &cost)
{
    typedef pair<weight_t, vertex_t> heapElement;
    typedef set<heapElement> heap;
    
    cost = 0;
    
    graph::size_type n = G.size();
    vector<weight_t> scores(n, inf);
    scores[0] = 0;
    vector<vertex_t> parents(n, 0);

    graph mst(n);

    heap x;
    for (vertex_t u = 0; u < n; ++u)
    {
        x.insert(make_pair(scores[u], u));
        parents[u] = u;
    }
    
    while (!x.empty())
    {
        heapElement min = *x.begin();
        vertex_t u = min.second;
        weight_t w = min.first;
        
        x.erase(x.begin());
        addEdge(mst, u, parents[u], w);
        cost += w;

        for (size_t i = 0; i != G[u].size(); ++i)
        {
            vertex_t adj = G[u][i].first;
            heap::iterator it = x.find(make_pair(scores[adj], adj));
            if (it != x.end())
            {
                heapElement v = *it;
                if (v.first > G[u][i].second)
                {
                    x.erase(it);
                    v.first = G[u][i].second;
                    parents[v.second] = u;
                    scores[v.second] = v.first;
                    x.insert(v);
                }
            }
        }
    }

    return mst;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Invalid Arguments. Usage: primsMST 'test file'" << endl;
        return -1;
    }
    graph G = createGraph(argv[1]);
    cout << "Graph: " << endl;
    printGraph(G);
    cout << endl;
    
    weight_t cost = 0;
    graph mst = primsMST(G, cost);
    cout << "MST: " << endl;
    printGraph(mst);
    cout << endl;
    
    cout << "Cost of MST: " << cost << endl;
}
