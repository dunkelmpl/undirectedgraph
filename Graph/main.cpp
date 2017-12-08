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
        cout << "\nMinimum spanning tree(Kruskal) : " << endl;
        
        int totalWeight = 0;
        for (auto& edge : mstKruskal) {
            totalWeight += edge.weight;
            cout << edge.src << "->" << edge.dest << "(weight: " << edge.weight << ")\n";
        }
        cout << "Total weight : " << totalWeight << endl;

        vector<int> mstPrims = g.getPrimsMST();

        cout << "\nMinimum spanning tree(Prim's) : " << endl;

        totalWeight = 0;
        for (size_t vertice = 1; vertice < mstPrims.size(); vertice++) {
            int weight = g.getEdgeWeight(mstPrims[vertice], (int)vertice);
            totalWeight += weight;

            cout << mstPrims[vertice] << "->" << vertice << "(weight: " << weight << ")\n";
        }

        cout << "Total weight : " << totalWeight << endl;

        int start = 0;
        vector<int> paths;
        vector<int> sptDjikstra = g.getDjikstraSPT(start, paths);

        cout << "\nMinimum paths tree(Djikstra) : " << endl;
        for (size_t dest = 0; dest < sptDjikstra.size(); dest++) {
            if (dest != start) {
                vector<int> backPath;
                backPath.reserve(sptDjikstra.size());
                backPath.push_back(dest);

                int vertice = dest;
                while (vertice != start) {
                    backPath.push_back(paths[vertice]);
                    vertice = paths[vertice];
                }

                cout << "\n" << start << " --> " << dest << ":\n";

                bool first = true;
                for (int vertexIndex = (int)backPath.size() - 1; vertexIndex >= 0; vertexIndex--) {
                    if (!first) {
                        cout << " -> ";
                    }
                    else {
                        first = false;
                    }
                    cout << backPath[vertexIndex];
                }

                cout << ". Distance = " << sptDjikstra[dest] << endl;

            }
        }

    }

    _CrtDumpMemoryLeaks();

    return 0;
}
