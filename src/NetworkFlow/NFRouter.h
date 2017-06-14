//
// Created by Hong Man Hou on 4/6/2017.
//

#ifndef SRC_NFROUTER_H
#define SRC_NFROUTER_H
#include "../Common/Router.h"
#include <cassert>
#include <vector>

class NFRouter : public Router {
public:
    struct Edge {
        int end, cost, cap, rev;

        Edge(int end, int cost, int cap, int rev) : end(end), cost(cost), cap(cap), rev(rev) {}

        friend std::ostream& operator << (std::ostream &out, const Edge &e);
    };
private:
    const static int INF = 1000000000;

    int inds, indt;

    const static int MAXNODES = ((Board::MAX_BOARD_SIZE * Board::MAX_BOARD_SIZE) << 1) + 3;

    /// adjacency lists for the edges
    /// node (i, j, b), b = 0 means node at the upper layer
    /// b = 1 means node at the lower layer
    /// the the last index is one of the five (possible) edges
    /// for more info read documentation
    std::vector< std::vector<Edge> > edges;

    // find index from (x, y) coordinate
    int xyToIndex(int y, int x) {
        assert(y >= 1 && y <= DN && x >= 1 && x <= DM);
        return ((y - 1) * DM + x);
    }

    std::pair<int, int> indexToxy(int index);

    // add an edge along with its reverse into the graph
    void addEdge(int ia, int ib, int cost);

    // judge if a point is in the board
    bool inBoard(int y, int x);

    // find out or in node of a node
    int lower(int i);
    int upper(int i);

    // arrays used in Label Correcting algorithm
    std::vector<int> dist, index, parent;
    std::vector<bool> inqueue;

    // find the next augmenting path with lowest cost
    // using Label Correcting Algorithm
    bool findPath();

    // Plain floodfill(BFS) for pathfinding
    bool findOnePath();

    // augment flow along the shortest path
    void augment();

    int flow;
public:
    void set(int n, int m, int k);

    void reset();

    Board *route();

    bool OK();

    void print_status();
};


#endif //SRC_NFROUTER_H
