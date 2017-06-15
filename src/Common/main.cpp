//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int m, n;
    cin >>m >>n;
    Solver s;
    /*Board *b = s.solve(m, n, Solver::NF);
    ofstream fout("solution.txt");
    if (b) {
        fout << (*b) << endl;
        // router.print_status();
        delete b;
    }
    fout.close();*/

    /*Board* b2 = s.solve(m, n, Solver::AS);

    ofstream fout2("solution2.txt");
    if (b2) {
        fout2 << (*b2) << endl;
        delete b2;
    }
    fout2.close();
    */


    Board* b3 = s.solve(m, n, Solver::DC);
    ofstream fout3("solution3.txt");
    if (b3) {
        fout3 << (*b3) << endl;
        delete b3;
    }
    return 0;
}
