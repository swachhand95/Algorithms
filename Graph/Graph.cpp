#include "Graph.h"
#include <iostream>

Graph::Graph(std::size_t n, bool directed) : G(n), directed(directed), edges(0) { }

void Graph::addEdge(int u, int v)
{
    if (u < 0 || v < 0 || u >= G.size() || v >= G.size())
        return;
    G[u].push_back(v);
    if (!directed)
        G[v].push_back(u);
    ++edges;
}

const std::vector<std::vector<int> >& Graph::getGraph() const
{
    return G;
}

std::size_t Graph::getNumEdges() const
{
    return edges;
}

std::size_t Graph::getNumNodes() const
{
    return G.size();
}

void Graph::printGraph() const
{
    for (size_t u = 0; u != getNumNodes(); ++u)
    {
        std::cout << u << ": ";
        for (auto v : G[u])
            std::cout << v << " ";
        std::cout << std::endl;
    }
}

