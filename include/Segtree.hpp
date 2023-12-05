#ifndef SEGTREE_H
#define SEGTREE_H

struct Matrix{
    unsigned long long int m11,m12,m21,m22;
};

struct Vector {
    unsigned long long int x, y;
};

struct Node {
    int t1, t2;
    Matrix matrix;
};

class SegTree {
public:
    SegTree(int n);
    void update(int idx, unsigned long long int matrix[2][2]);
    Vector query(int t0, int td, int x,  int y);

private:
    int nextPowerOfTwo(int n);
    void build(int node, int t1, int t2);
    void update(int node, int idx, unsigned long long int matrix[2][2]);
    Matrix query(int node, int t1, int t2, int t0, int td);

    int size;
    Node* tree;
    const unsigned long long int MOD = 100000000;  
};

#endif 