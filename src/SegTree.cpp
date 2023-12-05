#include "Segtree.hpp"
#include <iostream>

using namespace std;

void printMatrix(const Matrix& mat) {
    cout << "Matrix: \n";
    std::cout << mat.m11 << " " << mat.m12 << std::endl;
    std::cout << mat.m21 << " " << mat.m22 << std::endl;
    cout << "\n\n";
}

void printVector(const Vector& vet) {
    cout << "Vetor: \n";
    std::cout << vet.x << " " << vet.y << std::endl;
    cout << "\n\n";
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    Matrix result;
    unsigned long long int mod = 100000000;
    result.m11 = (A.m11 * B.m11 + A.m12 * B.m21) % mod;
    result.m12 = (A.m11 * B.m12 + A.m12 * B.m22) % mod;
    result.m21 = (A.m21 * B.m11 + A.m22 * B.m21) % mod;
    result.m22 = (A.m21 * B.m12 + A.m22 * B.m22) % mod;
    return result;
}

Vector multiplyVectorMatrix(const Vector& v, const Matrix& m) {
    Vector result;
    unsigned long long int mod = 100000000; 

    result.x = (v.x * m.m11 + v.y * m.m12) % mod;
    result.y = (v.x * m.m21 + v.y * m.m22) % mod;

    return result;
}

SegTree::SegTree(int n) {
    size = nextPowerOfTwo(n);
    tree = new Node[2 * size];
    size = n;
    build(1, 0, n - 1);
}

int SegTree::nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}

void SegTree::build(int node, int t1, int t2) {
    tree[node] = {t1, t2, {1, 0, 0, 1}};

    if (t1 == t2) {
        return;
    }

    int mid = (t1 + t2) / 2;
    build(2 * node, t1, mid);
    build(2 * node + 1, mid + 1, t2);
}

void SegTree::update(int idx, unsigned long long int matrix[2][2]) {
    update(1, idx, matrix);
}

void SegTree::update(int node, int idx, unsigned long long int matrix[2][2]) {
    if (tree[node].t1 == tree[node].t2 && tree[node].t1 == idx) {
        tree[node].matrix.m11 = matrix[0][0];
        tree[node].matrix.m12 = matrix[0][1];
        tree[node].matrix.m21 = matrix[1][0];
        tree[node].matrix.m22 = matrix[1][1];
        return;
    }

    int mid = (tree[node].t1 + tree[node].t2) / 2;
    if (idx <= mid) {
        update(2 * node, idx, matrix);
    } else {
        update(2 * node + 1, idx, matrix);
    }

    tree[node].matrix = multiplyMatrices(tree[2*node].matrix, tree[2*node+1].matrix);
}


Vector SegTree::query(int t0, int td, int x, int y) {
    Matrix result = query(1, 0, size - 1, t0, td);
    Vector v{x,y};
    Vector result2 =  multiplyVectorMatrix(v,result);
    return result2;

}

Matrix SegTree::query(int node, int start, int end, int t0, int td) {
    if (start > td || end < t0) {
        
        Matrix m{1, 0, 0, 1};
        return m;
    }

    if (start >= t0 && end <= td) {
        
        return tree[node].matrix;
    }

    int mid = (start + end) / 2;

    Matrix esquerda = query(2 * node, start, mid, t0, td);
    Matrix direita  = query(2 * node + 1, mid + 1, end, t0, td);

    Matrix result = multiplyMatrices(esquerda, direita);
    return result;
}