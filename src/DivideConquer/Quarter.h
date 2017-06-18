#ifndef SRC_QUARTER_H
#define SRC_QUARTER_H
#include "../NetworkFlow/NFRouter.h"
class Quarter : public NFRouter
{
private:
    bool fulfill();
public:
    void set(int n,int m,int k);
	bool flag;
	bool slink(int, int);
	bool tlink(int, int);
};

#endif //SRC_QUARTER_H
