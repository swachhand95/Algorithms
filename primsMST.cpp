#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>

typedef int vertex_t;
typedef long long int weight_t;
typedef std::pair< vertex_t, weight_t > neighbor;
typedef std::vector< std::vector< neighbor > > graph_t;
weight_t inf = std::numeric_limits<weight_t>::max();

void addEdge(graph_t &G, vertex_t u, vertex_t v, weight_t w)
{
    if (u < G.size() && v < G.size() && v != u)
    {
        G[u].push_back(std::make_pair(v, w));
        G[v].push_back(std::make_pair(u, w));
    }
}

graph_t primsMST(const graph_t &G, weight_t &cost)
{
    size_t n = G.size();
    cost = 0;

    graph_t mst(n);
    std::vector<bool> visited(n);

    vertex_t src = 0;
    visited[src] = true;

    size_t rem = n - 1;
    while (rem--)
    {
        vertex_t minU = 0, minV = 0;
        weight_t minCost = inf;

        for (vertex_t u = 0; u != visited.size(); ++u)
        {
            if (visited[u] == true)
            {
                for (size_t i = 0; i < G[u].size(); ++i)
                {
                    neighbor v = G[u][i];

                    if (visited[v.first] == false)
                    {
                        if (v.second < minCost)
                        {
                            minCost = v.second;
                            minU = u;
                            minV = v.first;
                        }
                    }
                }
            }

        }
    
        cost += minCost;
        addEdge(mst, minU, minV, minCost);
        visited[minV] = true;
    }

    return mst;
}

graph_t createGraph(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "Could not open file. Returning empty graph." << std::endl;
        return graph_t();
    }

    int n = 0, m = 0;
    fin >> n >> m;
    graph_t G(n);

    std::cout << "n = " << n << " m = " << m << std::endl;
    for (int i = 0; i != m; ++i)
    {
        vertex_t u = 0, v = 0;
        weight_t w = 0;

        fin >> u >> v >> w;

        addEdge(G, u - 1, v - 1, w);
    }

    return G;
}

void printGraph(const graph_t &G)
{
    for (int u = 0; u < G.size(); ++u)
    {
        std::cout << u << ": ";
        for (const auto &i : G[u])
            std::cout << i.first << "," << i.second << " ";
        std::cout << std::endl;
    }
}


int main(int argc, char *argv[])
{
    graph_t G = createGraph("edges.txt");

    weight_t mstCost = 0;
    graph_t mst = primsMST(G, mstCost);

    std::cout << "MST = " << std::endl;
    printGraph(mst);
    std::cout << "MST Cost = " << mstCost << std::endl;
    return 0;
}
