#include "Solver.h"
#include "../NetWorkFlow/NFRouter.h"
#include "../AStar/AstarRouter.h"
#include "../DivideConquer/DCRouter.h"
#include <iostream>

using namespace std;

Board* Solver::solve(int m,int n,RouterType type)
{
    int scale = (m > n) ? m : n;
    Router* router = NULL;
    switch(type)
    {
        case NF:
            cout <<"type is NF" <<endl;
            router = new NFRouter();
            break;
        case AS:
            cout <<"type is AS" <<endl;
            router = new AStarRouter();
            break;
        case DC:
            cout <<"type is DC" <<endl;
            router = new DCRouter();
            break;
        default:
            router = new NFRouter();
            break;
    }
    int l = scale / 4;
    router -> set(n, m , l);
    cout <<"Start testing ... " <<endl;
    while (!(router -> OK())) {
        cout <<l <<" cannot do " <<endl;
        l++;
        router -> set(n, m , l);
    }
    // cout <<"searching complete!" <<endl;
    cout <<"shortest is " <<l <<endl;
    router -> set(n, m , l);
    Board* b = router->route();
    cout <<"Successfully routed " <<router->get_flow() <<endl;
    cout <<"Cost is " <<router->get_cost() <<endl;
    cout <<endl;
    delete router;
    return b;
}
