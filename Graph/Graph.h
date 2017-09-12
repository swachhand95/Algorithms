#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
    public:
        Graph(std::size_t n, bool directed);
        void addEdge(int u, int v);
        const std::vector<std::vector<int> >& getGraph() const;
        std::size_t getNumNodes() const;
        std::size_t getNumEdges() const;
        void printGraph() const;
    private:
        std::vector<std::vector<int> > G;
        bool directed;
        std::size_t edges;
};

#endif // GRAPH_H
