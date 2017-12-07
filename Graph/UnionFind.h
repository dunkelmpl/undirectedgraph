#pragma once

#include <vector>

using namespace std;

class UnionFind
{
public:
    UnionFind(size_t size);
    virtual ~UnionFind();

public:
    void reset();

public:
    int findRoot(int item);
    void unite(int itemX, int itemY);
    bool isCyclic(int itemX, int itemY);

protected:
    void resetParents();

private:
    vector<int> parent;
    vector<int> ranks;
};

