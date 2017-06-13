#include "Router.h"

void Router::set(int n, int m, int k) {
    N = n; M = m; K = k;
    DN = n * (k + 1) + k; DM = m * (k + 1) + k; DMN = DM * DN;
}

void Router::reset() {
    N = M = K = DN = DM = DMN = 0;
}