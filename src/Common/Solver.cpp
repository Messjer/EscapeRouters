#include "Solver.h"
#include "../NetWorkFlow/NFRouter.h"
#include "../Rule/RuleRouter.h"
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
            router = new NFRouter();
            break;
        case RU:
            router = new RuleRouter();
            break;
        case DC:
            router = new DCRouter();
            break;
        default:
            router = new NFRouter();
            break;
    }
    int l = scale / 4;
    router -> set(n, m , l);
    cout <<"Start solving ... " <<endl;
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
    flow = router->get_flow(); cost = router->get_cost();
    cout <<"Cost is " <<router->get_cost() <<endl;
    cout <<endl;
    delete router;
    return b;
}
