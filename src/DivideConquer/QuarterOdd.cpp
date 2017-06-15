#include "QuarterOdd.h"
bool QuarterOdd::fulfill() {
    return flow == N * M - N;
}

void QuarterOdd::set(int n, int m, int k)
{
    reset();
    Router::set(n, m, k);

    edges.resize(DMN * 2 + 5);
    dist.resize(DMN * 2 + 5); index.resize(DMN * 2 + 5); parent.resize(DMN * 2 + 5); inqueue.resize(DMN * 2 + 5);
    inds = 0; indt = (xyToIndex(DN, DM) << 1) + 1;
    flow = 0; cost = 0;
    // add edges from source to terminals
    for (int i = 1; i <= n; i++)
        for (int j = 2; j <= m; j++)
            addEdge(inds, xyToIndex((k + 1) * i, (k + 1) * j), 0);
    //for(int j = 1; j <= m; j++)
    //	addEdge(inds, xyToIndex(1, (k + 1) * j),0);

    // add cost 1 edges between in nodes and out nodes
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            addEdge(xyToIndex(i, j), lower(xyToIndex(i, j)), 1);

    // add edges between out nodes and neighbors
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            for (int dir = Board::UP; dir <= Board::LEFT; dir++)
            {
                int ni = i + Board::dy(dir), nj = j + Board::dx(dir);
                if (inBoard(ni, nj))
                    addEdge(lower(xyToIndex(i, j)), xyToIndex(ni, nj), 0);
                else if((j == DM && i <= DN - k) ||(i == 1 && j > k+1))
                    addEdge(lower(xyToIndex(i, j)), indt, 0);
            }
}