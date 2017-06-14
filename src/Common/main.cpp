//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include "../NetworkFlow/NFRouter.h"
#include "../AStar/AStarRouter.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int m, n;
    cin >>m >>n;
    Solver s;
    Board *b = s.solve(m, n, Solver::NF);
    ofstream fout("solution.txt");
    if (b) {
        fout << (*b) << endl;
        // router.print_status();
        delete b;
    }
    Router* router = new AStarRouter(m, n, m / 2);
    Board* b2 = router->route();

    ofstream fout2("solution2.txt");
    if (b2) {
        fout2 << (*b2) << endl;
        // router.print_status();
        delete b2;
    }
    return 0;
}