#include "Solver.h"
#include "../NetWorkFlow/NFRouter.h"
#include <iostream>

using namespace std;

Board* Solver::solve(int m,int n,RouterType type)
{
    int scale = (m > n) ? m : n;
    // int l = scale / 4, r = scale / 2;
    // int mid = (l + r) / 2;
    Router* router = NULL;
    switch(type)
    {
        case NF:
            router = new NFRouter();
            break;
        case AS:
            //router = new ASRouter(m, n, mid);
            break;
        default:
            router = new NFRouter();
            break;
    }
    /*
    while(l < r)
    {

        cout <<"( " <<l <<" , " <<mid <<" , " <<r <<" ) "<<endl;
        router -> set(n, m, mid);

        if(router->OK()) {
            r = mid;
        }
        else l = mid + 1;
        mid = (l + r) /2;
    } */
    int l = scale / 4;
    router -> set(n, m , l);
    while (!(router -> OK())) {
        l++;
        router -> set(n, m , l);
    }
    // cout <<"binary search complete!" <<endl;
    cout <<"shortest is " <<l <<endl;
    router -> set(n, m , l);
    Board* b = router->route();
    cout <<"cost is " <<router->cost <<endl;
    delete router;
    return b;
}
