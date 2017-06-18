#include "Quarter.h"
bool Quarter::fulfill() {
	if(flag)return flow == N * M - N + 1 ;
	else    return flow == N * M ;
}

bool Quarter::slink(int i, int j)
{
	if(flag)
	 	 return (i < N && j > 1)  ||
                (j == 1 && !( ( N - i ) % 2 )) ||
                        (i == N && !( j % 2 )) ;
	else return true ;
}

bool Quarter::tlink(int i, int j)
{
	if(flag)
	{
		if(N % 2)
			return (j == DM && i < DN - K)       ||
                    (i == 1 && j >= K + 1) ;
		else 
			return (j == DM && i <= DN - K)      ||
                    (i == 1 && j > K + 1) ;
	}
	else 
	{
		if(K % 2)
			return (j == DM && i <= DN - K / 2)  ||
                    (i == 1 && j > K / 2 + 1) ;
		else 
			return (j == DM && i <= DN - K / 2)   ||
                    (i == 1 && j > K / 2) ;
	}
}

void Quarter::set(int n, int m, int k)
{
    reset();
    Router::set(n, m, k);

    edges.resize(DMN * 2 + 5);
    dist.resize(DMN * 2 + 5); index.resize(DMN * 2 + 5); parent.resize(DMN * 2 + 5); inqueue.resize(DMN * 2 + 5);
    inds = 0; indt = (xyToIndex(DN, DM) << 1) + 1;
    flow = 0; cost = 0;
    // add edges from source to terminals
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if(slink(i, j)) 
				addEdge(inds, xyToIndex((k + 1) * i, (k + 1) * j), 0);
		//	else if( j != 1 || i != N)
		//	{
		//		addEdge(inds, xyToIndex((k + 1) * i, (k + 1) * j), 0);
		//		addEdge(lower(xyToIndex((k + 1) * i, (k + 1) * j)), indt, 0);
		//	}
    //for(int j = 1; j <= m; j++)
    //	addEdge(inds, xyToIndex(1, (k + 1) * j),0);

    // add cost 1 edges between in nodes and out nodes
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
		{
		   	if(i % ( k + 1 ) || j % ( k + 1 ))
				addEdge(xyToIndex(i, j), lower(xyToIndex(i, j)), 1);
			else
			{
				int _i = i / (k + 1), _j = j / (k + 1);
				if(slink(_i, _j) || (j == 1 && i == N))
					addEdge(xyToIndex(i, j), lower(xyToIndex(i, j)), 1);
				else
					addEdge(xyToIndex(i, j), lower(xyToIndex(i, j)), 0, 0);
			}
		}
    // add edges between out nodes and neighbors
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            for (int dir = Board::UP; dir <= Board::LEFT; dir++)
            {
                int ni = i + Board::dy(dir), nj = j + Board::dx(dir);
                if (inBoard(ni, nj))
					addEdge(lower(xyToIndex(i, j)), xyToIndex(ni, nj), 0);
                else if (tlink(i, j))
					addEdge(lower(xyToIndex(i, j)), indt, 0);
				else 
					addEdge(lower(xyToIndex(i, j)), indt, 0, 0);
            }
}
