#ifndef UNIONFIND_H_INCLUDED
#define UNIONFIND_H_INCLUDED

class UnionFind
{
    typedef long long int size_type;
    typedef long long int node;
public:
    UnionFind(size_type size);
    ~UnionFind();
    void connect(node p, node q);
    bool connected(node p, node q);
private:
    node* id;
    node* sz;
    size_type n;
    node root(node p);
};

#endif // UNIONFIND_H_INCLUDED
