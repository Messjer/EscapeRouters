#ifndef SRC_TIMER_H
#define SRC_TIMER_H
#include "Solver.h"
#include "Board.h"
#include <string>
class Timer
{
public:
    Timer(int mm, int nn):m(mm),n(nn){}
    void timedTest(Solver::RouterType);
private:
    int m, n;
};


#endif ///Timer.h
