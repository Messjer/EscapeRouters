//
// Created by Hong Man Hou on 4/6/2017.
//

#include "NFRouter.h"
#include <iostream>
#include <queue>

using namespace std;

void NFRouter::addEdge(int ia, int ib, int cost) {
    edges[ia].push_back(Edge(ib, cost, 1, edges[ib].size()));
    edges[ib].push_back(Edge(ia, -cost, 0, edges[ia].size() - 1));
}

bool NFRouter::inBoard(int y, int x) {
    return (x >= 1 && x <= DM && y >= 1 && y <= DN);
}

std::pair<int, int> NFRouter::indexToxy(int index) {
    index %= DN * DM;
    return make_pair((index - 1) / DM + 1, 1 + (index - 1) % DM);
};

NFRouter::NFRouter(int n, int m, int k) : Router(n, m, k), flow(0), cost(0) {
    // add edges from source to terminals
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            addEdge(inds, xyToIndex((k + 1) * i, (k + 1) * j), 0);

    // add cost 1 edges between in nodes and out nodes
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            addEdge(xyToIndex(i, j), lower(xyToIndex(i, j)), 1);

    // add edges between out nodes and neighbors
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            for (int dir = Board::UP; dir <= Board::LEFT; dir++) {
                int ni = i + Board::dy(dir), nj = j + Board::dx(dir);
                if (inBoard(ni, nj))
                    addEdge(lower(xyToIndex(i, j)), xyToIndex(ni, nj), 0);
                else
                    addEdge(lower(xyToIndex(i, j)), indt, 0);
            }
}

ostream& operator << (ostream &out, const NFRouter::Edge &e){
    out <<" (end : " <<e.end <<" cap : " <<e.cap <<" rev : " <<e.rev  <<" ) ";
    return out;
}

int NFRouter::lower(int i) {
    assert(i >= 1 && i <= DN * DM);
    return i + DN * DM;
}

int NFRouter::upper(int i) {
    assert(i >= 1 + DN * DM && i <= (DN * DM << 1));
    return i - DN * DM;
}

void NFRouter::print_status() {
    cout <<"Edges are ... " <<endl;
    for (int i = 0; i <= indt; i++) {
        pair<int, int> node = indexToxy(i);
        cout <<"N( " <<node.first <<" , " <<node.second <<" ) " <<endl;
        for (int j = 0; j < edges[i].size(); j++) {
            cout <<edges[i][j] <<(j + 1 != edges[i].size() ? "," : "");
        }
        cout <<endl;
    }
}

bool NFRouter::findPath() {
    for (int i = 0; i <= indt; i++) dist[i] = INF;
    queue<int> q;
    q.push(inds);
    dist[inds] = 0;
    while (!q.empty()) {
        int a = q.front();
        q.pop();
        inqueue[a] = false;
        for (int i = 0; i < edges[a].size(); i++) {
            Edge &e = edges[a][i];
            int b = e.end;

            if (e.cap > 0 && dist[a] + e.cost < dist[b]) {
                dist[b] = dist[a] + e.cost;
                parent[b] = a;
                index[b] = i;

                if (!inqueue[b]) {
                    q.push(b);
                    inqueue[b] = true;
                }
            }
        }
    }
    return dist[indt] != INF;
}

void NFRouter::augment() {
    assert(dist[indt] != INF);
    int df = INF;
    int b = indt, a;

    while ((a = parent[b]) != -1) {
        Edge & e = edges[a][index[b]];
        df = min(df, e.cap);
        b = a;
    }

    b = indt;

    // cout <<"Path is  " <<endl;
    while ((a = parent[b]) != -1) {
        // compute edge and reverse edge
        pair<int, int> node = indexToxy(a);
        // cout <<" ( " <<node.first <<" , " <<node.second <<" ), ";
        Edge & e = edges[a][index[b]];
        Edge & re = edges[b][e.rev];
        e.cap -= df;
        re.cap += df;
        b = a;
    }
    // cout <<endl;
    flow += df;
    cost += df * dist[indt];
}

Board * NFRouter::route(){
    parent[inds] = -1;
    while (findPath()) {
        augment();
    }

    if (flow != N * M) return NULL;
    Board *rst = new Board(N, M, K);
    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++) {
            int outNode = lower(xyToIndex(i, j));
            for (int k = Board::UP; k <= Board::LEFT; k++)
                if (edges[outNode][k].cap == 0) {
                    // if this edge is used, put the number on the board
                    rst->table[i][j] = k;
                }
        }
    // cout <<(*rst) <<endl;
    return rst;
}
