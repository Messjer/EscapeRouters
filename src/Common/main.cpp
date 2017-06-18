<<<<<<< HEAD
//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include "../NetworkFlow/NFRouter.h"
#include "../AStar/AstarRouter.h"
#include "../Rule/RuleRouter.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    /*int m, n;
    cin >>m >>n;
    Solver s;
    Board *b = s.solve(m, n, Solver::NF);
    ofstream fout("solution.txt");
    if (b) {
        fout << (*b) << endl;
        // router.print_status();
        delete b;
    }

    Board* b2 = s.solve(m, n, Solver::AS);

    ofstream fout2("solution2.txt");
    if (b2) {
        fout2 << (*b2) << endl;
        // router.print_status();
        delete b2;
    }*/

    RuleRouter router;
    router.set(19, 19, 5);
    Board* b = router.route();
    ofstream fout("../Common/solution5.txt");
    fout << (*b) << endl;
    cout << "flow: " << router.get_flow() << endl;
    cout << "cost: " << router.get_cost() << endl;

    return 0;
}
=
