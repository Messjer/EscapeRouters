//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include "../NetworkFlow/NFRouter.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Solver s;
    Board *b = s.solve(30, 30, Solver::NF);
    ofstream fout("solution.txt");
    if (b) {
        fout << (*b) << endl;
        // router.print_status();
        delete b;
    }
    return 0;
}