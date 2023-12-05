#include <iostream>
#include "Segtree.hpp"

int main() {
    int n, q;
    std::cin >> n >> q;

    SegTree segtree(n);

    for (int i = 0; i < q; ++i) {
        char op;
        std::cin >> op;

        if (op == 'u') {
            int a;
            std::cin >> a;

            unsigned long long int matrix[2][2];
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    std::cin >> matrix[j][k];
                }
            }

            segtree.update(a, matrix);
        } else if (op == 'q') {
            int t0, td;
            unsigned long long int x,y;
            std::cin >> t0 >> td >> x >> y;

            Vector v = segtree.query(t0, td, x, y);
            std::cout << v.x << " " << v.y << std::endl;
        }
    }

    return 0;
}