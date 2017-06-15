#ifndef SRC_SOLVER_H
#define SRC_SOLVER_H
#include "Router.h"
#include "Board.h"

class Solver
{
public:
    enum RouterType {
        NF, AS, DC
    };
    Board* solve(int, int, RouterType);
};

#endif //SRc_SOLVER_H
