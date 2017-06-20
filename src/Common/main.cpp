//
// Created by Hong Man Hou on 7/6/2017.
//
#include "Timer.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    cout <<"Please enter dimension (m x n) ..." <<endl;
    cout <<"Default option is to use Rule Router for m = n, and NetworkFlow Router for m != n" <<endl;
    cout <<"... "
    int m, n;
    cin >>m >>n;
    Timer timer(m, n);
    if (m != n)
        timer.timedTest(Solver::NF);
    else
        timer.timedTest(Solver::RU);
    return 0;
}
