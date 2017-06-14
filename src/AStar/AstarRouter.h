#ifndef SRC_ASTARROUTER_H
#define SRC_ASTARROUTER_H



#include "../Common/Router.h"
#include <vector>
#include <algorithm>
#include <list>

static const int dx[5] = {0, -1, 0, 1, };

static const int dy[5] = {0, 0, 1, 0, -1};

class AStarRouter : public Router
{
public:
    enum Status {
        NOVISITED = 0,
        VISITED = 1,
        CLOSED = 2,
    };

    enum Axis {
        Xs = 0,
        Ys,
        Min,
        Max,
    };

    struct Point
    {
        int status;
        int pre_direct;
        int direct;
        int expect_cost[4];
        int cost;
        int expect_value;
        int index;

        Point() = default;

        bool operator < (const Point &b) const {
            return expect_value < b.expect_value;
        }
    };

private:
    std::vector<std::vector<Point>> map;
    std::vector<int> openList;
    std::vector<int> closeList;

public:
    void set(int n, int m, int k);

    void reset();
    void find_route(int x, int y);

    void cal_expect_cost(Point &p);
    void set_direct(int x, int y, int pre_direct);
    void find_minPoint(int &minIndex);
    void clean(int index);
    void round_search(int k);

    int getIndex(int x, int y) {
        return y * DN + x;
    }

    void getXY(int index, int &x, int &y) {
        y = index / DN;
        x = index % DN;
    }

    bool valid(int x, int y) {
        return (x < DN && x >= 0 && y >= 0 && y < DM);
    }

    Board* route();

    bool OK(){
        int m = M, n = N, k = K;
        Board *b = route();
        delete b;
        int f = flow;
        reset(); set(m, n, k);
        std::cout <<f <<std::endl;
        return f == M * N;
    }
    void print_status(){}

};


#endif //SRC_ASTARROUTER_H
