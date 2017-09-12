#include "UnionFind.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// For debugging purposes only!
#define PR(X) cout << #X << "=" << X << endl

struct Edge
{
    int u;
    int v;
    Edge(int a, int b) : u{a}, v{b} { }
};

int random_edge(int sz)
{
    random_device rd;  // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(0, sz - 1); // define the range
    return distr(eng);
}

int minCut(const vector<vector<int>>& G)
{
    vector<Edge> E;
    for (int i = 0; i < G.size(); ++i)
    {
        int u = G[i][0];
        for (int j = 1; j < G[i].size(); ++j)
            if (u < G[i][j])
                E.push_back(Edge(u, G[i][j]));
    }

    UnionFind uf(G.size());
    for (int i = 0; i < G.size() - 2; ++i)
    {
        int idx = random_edge(E.size());
        if (!uf.connected(E[idx].u, E[idx].v))
        {
            uf.connect(E[idx].u, E[idx].v);
        }
        E.erase(E.begin() + idx);

        for (int j = 0; j < E.size(); ++j)
        {
            if (uf.connected(E[j].u, E[j].v))
                E.erase(E.begin() + j);
        }
    }

    int crossingEdges = 0;
    for (int i = 0; i < E.size(); ++i)
        if (!uf.connected(E[i].u, E[i].v))
            ++crossingEdges;
    return crossingEdges;
}

vector<vector<int>> get_input(const string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return vector<vector<int>>();

    vector<vector<int>> g;

    string line;
    while (getline(fin, line))
    {
        stringstream ls(line);
        vector<int> adj;

        int n = 0;
        while (ls >> n)
            adj.push_back(n - 1);

        g.push_back(adj);
    }


    for (int i = 0; i < g.size(); ++i)
    {
        for (int j = 0; j < g[i].size(); ++j)
            cout << g[i][j] << " ";
        cout << endl;
    }

    return g;
}

void ufTest()
{
    UnionFind uf(5);
    uf.connect(0, 2);
    cout << uf.connected(0, 2) << endl;
    cout << uf.connected(2, 3) << endl;
    uf.connect(3, 2);
    cout << uf.connected(2, 3) << endl;
}

int main()
{
    vector<vector<int> > G = get_input("kargerMinCut.txt");
    int smallest = -1;
    int mincut = -1;
    PR(G.size()*G.size());
    for (size_t i = 0; i < G.size(); ++i)
    {
        mincut = minCut(G);
        if (smallest == -1 || mincut < smallest)
            smallest = mincut;
        if (i%1000 == 0)
            PR(i);
    }
    PR(smallest);
    return 0;
}
