#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H 

#include <vector>

class WeightedGraph
{
    public:
        struct Node
        {
            int v;
            double wt;
            Node(int node, int cost) : v(node), wt(cost) { }
        };
        WeightedGraph(std::size_t n, bool directed);
        void addEdge(int u, int v, double wt);
        const std::vector<std::vector<Node> >& getGraph() const;
        std::size_t getNumNodes() const;
        std::size_t getNumEdges() const;
        void printGraph() const;
    private:
        std::vector<std::vector<Node> > G;
        bool directed;
        std::size_t edges;
};

#endif // WEIGHTEDGRAPH_H
