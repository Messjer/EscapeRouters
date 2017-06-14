#include "Solver.h"
#include "../NetWorkFlow/NFRouter.h"
#include "../Astar/AstarRouter.h"
#include <iostream>

using namespace std;

Board* Solver::solve(int m,int n,RouterType type)
{
    int scale = (m > n) ? m : n;
    Router* router = NULL;
    switch(type)
    {
        case NF:
            router = new NFRouter();
            break;
        case AS:
            router = new AStarRouter();
            break;
        default:
            router = new NFRouter();
            break;
    }
    int l = scale / 4;
    router -> set(n, m , l);
    while (!(router -> OK())) {
        cout <<l <<" cannot do " <<endl;
        l++;
        router -> set(n, m , l);
    }
    // cout <<"searching complete!" <<endl;
    cout <<"shortest is " <<l <<endl;
    router -> set(n, m , l);
    Board* b = router->route();
    cout <<"cost is " <<router->cost <<endl;
    delete router;
    return b;
}
