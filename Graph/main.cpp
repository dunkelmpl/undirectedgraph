#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

#include "Graph.h"

using namespace std;

int main()
{
    {
        Graph g(9);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 7, 8);
        g.addEdge(1, 2, 8);
        g.addEdge(1, 7, 11);
        g.addEdge(2, 5, 4);
        g.addEdge(2, 3, 7);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 14);
        g.addEdge(5, 4, 10);
        g.addEdge(6, 5, 2);
        g.addEdge(7, 6, 1);
        g.addEdge(7, 8, 7);
        g.addEdge(8, 2, 2);
        g.addEdge(8, 6, 6);

        //cout << "Graph " << (g.isCyclic() ? "contains" : "does not contain") << " cycle(s)" << endl;

        vector<GraphEdge> mstKruskal = g.getKruskalMST();
        cout << "Minimum spanning tree(Kruskal) : " << endl;

        for (auto& edge : mstKruskal) {
            cout << edge.src << "->" << edge.dest << "(weight: " << edge.weight << ")\n";
        }

        vector<int> mstPrims = g.getPrimsMST();
        cout << "Minimum spanning tree(Prim's) : " << endl;

        for (size_t vertice = 1; vertice < mstPrims.size(); vertice++) {
            cout << mstPrims[vertice] << "->" <<
                vertice << "(weight: " << g.getEdgeWeight(mstPrims[vertice], vertice) << ")\n";
        }
    }

    _CrtDumpMemoryLeaks();

    return 0;
}