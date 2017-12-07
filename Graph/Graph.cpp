#include <stdexcept>
#include <algorithm>

#include "Graph.h"

Graph::~Graph()
{
}

void Graph::addEdge(int itemX, int itemY, int weight /* = 1 */)
{
    if (itemX >= (int)edges.size() || itemY >= (int)edges.size()) {
        throw overflow_error("Invalid edge specified");
    }

    edges[itemX][itemY] = weight;
}

bool Graph::isCyclic()
{
    bool cycleFound = false;

    UnionFind uf(edges.size());

    for (int from = 0; !cycleFound && from < (int)edges.size(); from++) {
        for (unordered_map<int, int>::iterator& it = edges[from].begin(); it != edges[from].end(); it++) {
            int to = (*it).first;
            if ((from != to) && uf.isCyclic(from, to)) {
                cycleFound = true;

                break;
            }
            else {
                uf.unite(from, to);
            }
        }
    }

    return cycleFound;
}

vector<GraphEdge> Graph::getAllSortedEdges()
{
    vector<GraphEdge> allEdges;

    for (size_t from = 0; from < edges.size(); from++) {
        for (pair<const int, int>& to : this->edges[from]) {
            allEdges.push_back(GraphEdge(from, to.first, to.second));
        }
    }

    sort(
        allEdges.begin(),
        allEdges.end(),
        [](GraphEdge edge1, GraphEdge edge2) -> bool {
            return edge1.weight < edge2.weight;
        }
    );

    return allEdges;
}

vector<GraphEdge> Graph::getKruskalMST()
{
    vector<GraphEdge> allSortedEdges = this->getAllSortedEdges();

    vector<GraphEdge> mts;

    if (allSortedEdges.size() < 1) {
        return mts;
    }

    UnionFind uf(allSortedEdges.size());
    for (auto& edge : allSortedEdges) {
        if (false == uf.isCyclic(edge.src, edge.dest)) {
            mts.push_back(edge);
            uf.unite(edge.src, edge.dest);
        }
    }

    return mts;
}
