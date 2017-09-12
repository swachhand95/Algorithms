#include "Graph.h"
#include "WeightedGraph.h"
#include <iostream>

using namespace std;

int main()
{
    Graph G(5, false);
    G.addEdge(1, 2);
    G.addEdge(3, 2);
    G.addEdge(4, 0);
    G.addEdge(0, 6);
    G.addEdge(2, 4);
    G.addEdge(1, 3);

    cout << G.getNumNodes() << endl;
    cout << G.getNumEdges() << endl;
   
    cout << endl; 
    G.printGraph();

    WeightedGraph wg(6, true);
    wg.addEdge(0, 1, 1);
    wg.addEdge(0, 4, 2);
    wg.addEdge(1, 2, 1);
    wg.addEdge(2, 0, 1);
    wg.addEdge(2, 1, 3);
    wg.addEdge(3, 2, 1);
    wg.addEdge(4, 5, 3);
    wg.addEdge(5, 4, 2);

    cout << wg.getNumNodes() << endl;
    cout << wg.getNumEdges() << endl;

    cout << endl;
    wg.printGraph();
}
