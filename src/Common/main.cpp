//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include "Timer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // int m, n;
    // cin >>m >>n;
    for (int m = 5; m <= 70; m += 5) {
        Timer timer(m, m);
        if (m <= 60)
            timer.timedTest(Solver::NF);
        timer.timedTest(Solver::DC);
        if (m >= 25)
            break;
    }
    return 0;
}
