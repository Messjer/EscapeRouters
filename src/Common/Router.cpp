#include "Router.h"

void Router::set(int n, int m, int k) {
    N = n; M = m; K = k;
    DN = n * (k + 1) + k; DM = m * (k + 1) + k; DMN = DM * DN;
}

void Router::reset() {
    N = M = K = DN = DM = DMN = 0;
}

bool Router::OK() {
    int m = M, n = N, k = K;
    Board *b = route();
    delete b;
    int f = flow;
    reset(); set(m, n, k);
    std::cout <<f <<std::endl;
    return fulfill();
}