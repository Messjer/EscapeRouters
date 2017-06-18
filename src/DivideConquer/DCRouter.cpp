#include "DCRouter.h"
#include "Quarter.h"
#include <queue>
#include <fstream>

Board* DCRouter::route()
{
    Quarter router;
	router.flag = N % 2;
    router.set( (N - 1 ) / 2 + 1, (M - 1) / 2 + 1, K);
    Board* qb = router.route();
    if(!qb)return NULL;

   /* for(int i = 1;i <= qb->DN; i++)
            if(qb->table[i][qb->DM])
			{
				int judege = 0;
				for(int dir = Board::UP; dir <= Board::LEFT; dir++)
				{
					int ni = i + Board::dy(dir), nj = j + Board::dx(dir);
					if (inBoard(ni, nj))
					
					if(qb->[ni][nj])judge++;
				}
				if(judge)qb->table[i][j] = 0;
			}
    for(int i = qb->DN-K+1; i <= qb->DN; i++)
        for(int j = 1;j <= qb->DM; j++)
            if(qb->table[i][j])qb->table[i][j] = 0;
	*/
	for(int i = 1; i <= qb->DN; i++)
	{
		if(!router.tlink(i, 1 ))     qb->table[i][1] = 0;
		if(!router.tlink(i, qb->DM)) qb->table[i][qb->DM] = 0;
	}
	for(int j = 1; j <= qb->DM; j++)
	{
		if(!router.tlink(1, j ))     qb->table[1][j] = 0;
		if(!router.tlink(qb->DN, j)) qb->table[qb->DN][j] = 0;
	}		
    
	
	// std::ofstream fout("solutionQ.txt");
    // fout << (*qb) << std::endl;
    
	Board* b = new Board(N, M, K);
	int is = 1, ie, js, je = qb->DM, dy;
	std::queue<int> q;
	if(router.flag)
	{
		int i = qb->DN - qb->K, j = qb->K + 1;
		int dir = 0, ni = 0, nj = 0, overcost = 0 ;
		while (i > 0 && j <= qb->DM)
		{
			dir = qb->table[i][j];
			ni = i + Board::dy(dir);
		   	nj = j + Board::dx(dir);
			q.push(dir);
			overcost++;
			qb->table[i][j] = 0 ;
			i = ni;
			j = nj;
		}
		cost = 4 * router.get_cost() - 3 * overcost ;
		flow = 4 * router.get_flow() - 3 ;
		ie = qb->DN - K;
		js = K + 1;
		dy = DM / 2 - K;
	}
	else
	{
			cost = 4 * router.get_cost();
			flow = 4 * router.get_flow();
			if(K % 2)
			{
				ie = qb->DN - K / 2;
				js = K / 2 + 2;
				dy = DM / 2 - K / 2;
			}
			else
			{
				ie = qb->DN - K / 2 + 1;
				js = K / 2 + 1;
				dy = DM / 2 - K / 2;
			}
	}
	for( int i = is; i <= ie; i++)
		for( int j =  js; j <= je; j++)
		{
			int x = i, y = j + dy;
	        int dir = qb->table[i][j];
		    if(dir)b->table[x][y] = dir;
	
	        dir = rotate(dir);
		    if(dir)b->table[y][DM - x + 1] = dir;
	
	        dir = rotate(dir);
			if(dir)b->table[DN - x + 1][DM - y + 1] = dir;
	
		    dir = rotate(dir);
		    if(dir)b->table[DN - y + 1][x] = dir;
        }
	if(router.flag)
	{
		int i = DN / 2 + 1, j = DM / 2 + 1 ;
		int dir;
		while(!q.empty())
		{
			dir = q.front();
			q.pop();
			b->table[i][j] = dir;
			i += Board::dy(dir);
		   	j += Board::dx(dir);
		}
	}
    delete qb;
    // fout.close();
    /*std::queue<int> q;
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
            if(b->table[i][j] < 0)b->table[i][j] = 0;*/
    return b;
}

bool DCRouter::OK()
{
    Quarter router;
	router.flag = N % 2;
    router.set((N - 1) / 2 + 1, (M - 1) / 2 + 1, K);
    bool ok = router.OK();
    return ok;
}

void DCRouter::print_status()
{
}
