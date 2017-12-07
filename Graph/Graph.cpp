#include <stdexcept>
#include <algorithm>

#include "Graph.h"

#define INF (INT_MAX)

Graph::~Graph()
{
}

void Graph::addEdge(int itemX, int itemY, int weight /* = 1 */)
{
    if (itemX >= (int)edges.size() || itemY >= (int)edges.size()) {
        throw overflow_error("Invalid edge specified");
    }

    int from = itemX < itemY ? itemX : itemY;
    int to = itemX == from ? itemY : itemX;

    edges[from][to] = weight;
    edges[to][from] = weight;
}

const int Graph::getEdgeWeight(int from, int to)
{
    return this->edges[from][to];
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

vector<int> Graph::getPrimsMST()
{
    const int numVertices = (int)edges.size();
    vector<int> parent(numVertices, -1);

    if (numVertices == 0) {
        return parent;
    }

    vector<bool> mstSet(numVertices, false);
    vector<int> nonMstSet(numVertices, INF);

    nonMstSet[0] = 0;
    int minNonMst = 0;

    // Number of vertices that supposed to be in the MST
    for (int vertice = 0; vertice < numVertices-1; vertice++) {
        minNonMst = [&mstSet, &nonMstSet]() -> int {
            int minNonMst = -1;
            int minNonMstWeight = INF;
            for (int item = 0; item < (int)nonMstSet.size(); item++) {
                if (mstSet[item] == false && nonMstSet[item] < minNonMstWeight) {
                    minNonMst = item;
                    minNonMstWeight = nonMstSet[item];
                }
            }

            return minNonMst;
        }();

        mstSet[minNonMst] = true;

        int minSibling = -1;
        int minSiblingWeight = INF;

        for (auto &siblingPair : edges[minNonMst]) {
            int sibling = siblingPair.first;
            int siblingWeight = siblingPair.second;
            if ((mstSet[sibling] == false) && (siblingWeight < nonMstSet[sibling])) {
                nonMstSet[sibling] = siblingWeight;
                parent[sibling] = minNonMst;
            }
        }
    }

    return parent;
}
