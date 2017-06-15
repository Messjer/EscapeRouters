#ifndef SRC_DCROUTER_H
#define SRC_DCROUTER_H
#include "../Common/Router.h"
class DCRouter:public Router
{
public:
    Board* route();
    void print_status();
    bool OK();
private:
    int xyToIndex(int y, int x)
    {
        assert(y >= 1 && y <= DN && x >= 1 && x <= DM);
        return ((y - 1) * DM + x);
    }
    int rotate(int dir)
    {
        return (dir)? dir % 4 + 1 : 0;
    }
    bool inBoard(int y, int x)
    {
        return (x >= 1 && x <= DM && y >= 1 && y <= DN);
    }
};

#endif //SRC_DCROUTER_H
