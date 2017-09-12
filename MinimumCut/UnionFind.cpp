#include "UnionFind.h"
#include <iostream>

using namespace std;

UnionFind::UnionFind(size_type size)
{
    n = size;
    id = new node[n];
    sz = new node[n];
    for (size_type i = 0; i < n; ++i)
    {
        id[i] = i;
        sz[i] = 1;
    }
}

UnionFind::~UnionFind()
{
    delete []id;
    delete []sz;
}

UnionFind::node UnionFind::root(node p)
{
    node i = id[p];
    while (i != id[i])
    {
        i = id[i];
    }
    return i;
}

bool UnionFind::connected(node p, node q)
{
    return root(p) == root(q);
}

// Using weighted union
void UnionFind::connect(node p, node q)
{
    node pRoot = root(p);
    node qRoot = root(q);
    if (pRoot == qRoot)
        return;
    if (sz[pRoot] < sz[qRoot])
    {
        id[pRoot] = qRoot;
        sz[qRoot] += sz[pRoot];
    }
    else
    {
        id[qRoot] = pRoot;
        sz[pRoot] += sz[qRoot];
    }
}
