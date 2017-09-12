#include "WeightedGraph.h"
#include <iostream>

WeightedGraph::WeightedGraph(std::size_t n, bool directed) :
    G(n), directed(directed), edges(0) { }


void WeightedGraph::addEdge(int u, int v, double wt)
{
    if (u < 0 || v < 0 || u >= G.size() || v >= G.size())
        return;
    G[u].push_back(Node(v, wt));
    if (!directed)
        G[v].push_back(Node(u, wt));
    ++edges;
}


const std::vector<std::vector<WeightedGraph::Node> >& WeightedGraph::getGraph() const
{
    return G;
}


std::size_t WeightedGraph::getNumEdges() const
{
    return edges;
}


std::size_t WeightedGraph::getNumNodes() const
{
    return G.size();
}


void WeightedGraph::printGraph() const
{
    for (size_t u = 0; u != getNumNodes(); ++u)
    {
        std::cout << u << ": ";
        for (auto node : G[u])
            std::cout << "(" << node.v << ", " << node.wt << ") ";
        std::cout << std::endl;
    }
}

