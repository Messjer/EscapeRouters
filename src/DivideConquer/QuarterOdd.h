#ifndef SRC_QUARTERODD_H
#define SRC_QUARTERODD_H
#include "../NetworkFlow/NFRouter.h"
class QuarterOdd : public NFRouter
{
private:
    bool fulfill();
public:
    void set(int n,int m,int k);
};

#endif //SRC_QUARTERODD_H
