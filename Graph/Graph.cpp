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
            allEdges.push_back(GraphEdge((int)from, to.first, to.second));
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

int Graph::getNextOptimalSourceVertice(vector<bool> currentInclusionSet, vector<int> currentVerticesWeights)
{
    int minWeight = INF;
    int minIndex = -1;
    for (int index = 0; index < (int)currentVerticesWeights.size(); index++) {
        if (!currentInclusionSet[index] && currentVerticesWeights[index] < minWeight) {
            minWeight = currentVerticesWeights[index];
            minIndex = index;
        }
    }

    return minIndex;
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
        minNonMst = this->getNextOptimalSourceVertice(mstSet, nonMstSet);

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

vector<int> Graph::getDjikstraSPT(int start, vector<int>& paths)
{
    int numVertices = (int)this->edges.size();
    if (start < 0 && start >= numVertices) {
        throw invalid_argument("Invalid shortest path tree start point");
    }

    vector<bool> sptSet(this->edges.size(), false);
    vector<int> nonSptSet(this->edges.size(), INF);
    vector<int> distances(this->edges.size(), 0);
    paths.assign(this->edges.size(), -1);

    nonSptSet[start] = 0;

    // All the vertices, excluding start one, cause it's calculated (to be zero) initially
    for (int vertice = 0; vertice < numVertices - 1; vertice++) {
        int srcVertice = this->getNextOptimalSourceVertice(sptSet, nonSptSet);

        nonSptSet[srcVertice] = true;

        for (auto& destVerticeData : this->edges[srcVertice]) {
            int destVertice = destVerticeData.first;
            int edgeWeight = destVerticeData.second;

            if (!nonSptSet[destVertice] && (edgeWeight < nonSptSet[destVertice])) {
                nonSptSet[destVertice] = edgeWeight;
                distances[destVertice] += edgeWeight;
                paths[destVertice] = srcVertice;
            }
        }
    }

    return distances;
}