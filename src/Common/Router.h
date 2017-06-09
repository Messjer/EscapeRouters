#ifndef SRC_ROUTER_H
#define SRC_ROUTER_H
#include "Board.h"
/// A base class for the routing process
/// Strategy pattern

class Router {
protected:
    int N, M, K;

    int DN, DM;
public:
    Router(int n, int m, int k) : N(n), M(m), K(k), DN(n * (k + 1) + k), DM(m * (k + 1) + k) {}

    /// this function implement the routing process
    /// @return NULL if infeasible, otherwise the optimal board
    virtual Board *route() = 0;
};

#endif //SRC_ROUTER_H
