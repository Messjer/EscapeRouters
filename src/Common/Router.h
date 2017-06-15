#ifndef SRC_ROUTER_H
#define SRC_ROUTER_H
#include "Board.h"
/// A base class for the routing process
/// Strategy pattern

class Router {
protected:
    int N, M, K;

    int DN = 1, DM = 1, DMN = 1;

    int cost, flow;
public:
    int get_cost() { return cost; }
    int get_flow() { return flow; }

    /// set the problem parameters
    virtual void set(int n, int m, int k);

    /// this function implement the routing process
    /// @return NULL if infeasible, otherwise the optimal board
    virtual Board *route() = 0;

    /// clear the parameters
    virtual void reset();

    /// this function check whether it is possible to route
    /// @return if the routing succeed
    virtual bool OK() = 0;

    virtual void print_status() = 0;
    virtual ~Router() {}
};

#endif //SRC_ROUTER_H
