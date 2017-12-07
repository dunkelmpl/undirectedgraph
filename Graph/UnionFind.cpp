#include "UnionFind.h"


UnionFind::UnionFind(size_t size) : parent(size), ranks(size)
{
    this->resetParents();
}

UnionFind::~UnionFind()
{
}

void UnionFind::reset()
{
    this->resetParents();
    ranks.assign(ranks.size(), 0);
}

void UnionFind::resetParents()
{
    for (size_t index = 0; index < parent.size(); index++) {
        parent[index] = (int)index;
    }
}

int UnionFind::findRoot(int item)
{
    while (item != parent[item]) {
        parent[item] = parent[parent[item]];
        item = parent[item];
    }

    return item;
}

bool UnionFind::isCyclic(int itemX, int itemY)
{
    return findRoot(itemX) == findRoot(itemY);
}

void UnionFind::unite(int itemX, int itemY)
{
    int rootX = findRoot(itemX);
    int rootY = findRoot(itemY);

    if (rootX == rootY) {
        return;
    }

    if (ranks[rootX] >= ranks[rootY]) {
        parent[rootY] = rootX;

        if (ranks[rootX] == ranks[rootY]) {
            ranks[rootX]++;
        }
    }
    else { 
        parent[rootX] = parent[rootY];
    }
}
