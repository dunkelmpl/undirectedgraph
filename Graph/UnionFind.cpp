#include "UnionFind.h"


UnionFind::UnionFind(size_t size) : parent(size), ranks(size)
{
    for (size_t index = 0; index < size; index++) {
        parent[index] = index;
    }
}

UnionFind::~UnionFind()
{
}

void UnionFind::reset()
{
    for (size_t index = 0; index < parent.size(); index++) {
        parent[index] = index;
    }

    ranks.assign(ranks.size(), 0);
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
