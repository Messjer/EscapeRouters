//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Solver.h"
#include "Timer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int m, n;
    cin >>m >>n;
    Timer timer(m, n);
	timer.timedTest(Solver::NF, "solution.txt");
	timer.timedTest(Solver::DC, "solution3.txt");
    return 0;
}
