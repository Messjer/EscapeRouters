#include "DCRouter.h"
#include "../DivideConquer/QuarterOdd.h"
#include <queue>
#include <fstream>
using namespace std;

Board* DCRouter::route()
{
    Router* router = NULL;
    if(N%2 && M%2)
        router = new QuarterOdd();
    router->set(N / 2 + 1, M / 2 + 1, K);
    Board* qb = router->route();
    cost = 4 * router->get_cost();
    flow = 4 * router->get_flow();
    delete router;
    if(!qb)return NULL;

    for(int i = 1;i <= qb->DN; i++)
        for(int j = 1;j <= qb->K; j++)
            if(qb->table[i][j])qb->table[i][j] = 0;
    for(int i = qb->DN-K+1; i <= qb->DN; i++)
        for(int j = 1;j <= qb->DM; j++)
            if(qb->table[i][j])qb->table[i][j] = 0;

    std::ofstream fout("solutionQ.txt");
    fout << (*qb) << endl;
    Board* b = new Board(N, M, K);
    for(int i = 1; i <= qb->DN-K; i++)
        for(int j =  2; j <= qb->DM - K; j++)
        {
            int x = i, y = qb->DM-K+j-1;
            int l = DM /2 + 1;
            int dir = qb->table[i][j+K];
            b->table[x][y] = dir;

            dir = rotate(dir);
            b->table[y][DM-x+1] = dir;

            dir = rotate(dir);
            b->table[DN-x+1][DM-y+1] = dir;

            dir = rotate(dir);
            b->table[DN-y+1][x] = dir;

        }
    delete qb;
    fout.close();
    std::queue<int> q;
    int cindex = xyToIndex(DN/2+1,DM/2+1);
    q.push(cindex);
    bool flag = true;
    int lastdir = 0;
    while(!q.empty())
    {
        int j = 1 + (q.front() - 1) % DM, i = q.front() / DM + 1;
        for (int dir = Board::UP; dir <= Board::LEFT; dir++)
        {
            int ni = i + Board::dy(dir), nj = j + Board::dx(dir);
            if(!inBoard(ni,nj))
            {
                lastdir = dir;
                flag = false;
                break;
            }
            if(!b->table[ni][nj])
            {
                b->table[ni][nj] = -dir;
                q.push(xyToIndex(ni,nj));
            }
        }
        if(flag)
            q.pop();
        else
            break;
    }

    int nowindex = q.front();
    int j = 1 + (nowindex - 1) % DM, i = nowindex / DM + 1;
    while(nowindex != cindex)
    {
        int dir = -b->table[i][j];
        b->table[i][j] = lastdir;
        int ni = i - Board::dy(dir), nj = j - Board::dx(dir);
        nowindex = xyToIndex(ni,nj);
        lastdir = dir;
        i = ni;j = nj;
        cost++;
    }
    cost++;
    b->table[i][j] = lastdir;
    flow++;
    for(int i = 1; i <= DN; i++)
        for(int j = 1; j <= DM; j++)
            if(b->table[i][j] < 0)b->table[i][j] = 0;
    return b;
}

bool DCRouter::OK()
{
    Router* router = NULL;
    if(N%2 && M%2)router = new QuarterOdd();
    router->set(N / 2 + 1, M / 2 + 1, K);
    bool ok = router->OK();
    delete router;
    return ok;
}

void DCRouter::print_status()
{
}
