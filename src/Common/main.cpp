//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Timer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // int m, n;
    // cin >>m >>n;
    for (int m = 10; m <= 30; m += 5) {
        Timer timer(m, m);
        if (m <= 60)
            timer.timedTest(Solver::NF);
        timer.timedTest(Solver::DC);
        timer.timedTest(Solver::RU);
    }

    return 0;
}
