#pragma once

#include <unordered_map>

#include "UnionFind.h"

using namespace std;

struct GraphEdge {
    GraphEdge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
    int src;
    int dest;
    int weight;
};

class Graph
{
public:
    Graph(size_t size) : edges(size) {}
    virtual ~Graph();

public:
    void addEdge(int itemX, int itemY, int weight = 1);
    bool isCyclic();
    vector<GraphEdge> getKruskalMST();

protected:
    vector<GraphEdge> getAllSortedEdges();

private:
    // weighted edges, wher vector[X] is source vertice,
    // map key is destination vertice and map value is edge's weight
    vector<unordered_map<int, int>> edges;
};

