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
    if (index > DMN)
        index -= DMN;
    return make_pair((index - 1) / DM + 1, 1 + (index - 1) % DM);
};

void NFRouter::set(int n, int m, int k) {
    reset();
    Router::set(n, m, k);

    edges.resize(DMN * 2 + 5);
    dist.resize(DMN * 2 + 5); index.resize(DMN * 2 + 5); parent.resize(DMN * 2 + 5); inqueue.resize(DMN * 2 + 5);
    inds = 0; indt = (xyToIndex(DN, DM) << 1) + 1;
    flow = 0; cost = 0;
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

void NFRouter::reset() {
    edges.clear();
    dist.clear(); index.clear(); parent.clear(); inqueue.clear();
    Router::reset();
}

ostream& operator << (ostream &out, const NFRouter::Edge &e){
    out <<" (end : " <<e.end <<" cap : " <<e.cap <<" rev : " <<e.rev  <<" ) ";
    return out;
}

int NFRouter::lower(int i) {
    assert(i >= 1 && i <= DMN);
    return i + DMN;
}

int NFRouter::upper(int i) {
    assert(i >= 1 + DMN && i <= (DMN << 1));
    return i - DMN;
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
    if (flow > 0) {
        int m = M, n = N, k = K;
        reset();
        set(m, n, k);
    }
    parent[inds] = -1;
    while (findPath()) {
        augment();
    }

    if (!fulfill()) return NULL;
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

bool NFRouter::findOnePath() {
    for (int i = 0; i <= indt; i++) dist[i] = INF;
    dist[inds] = 0;
    queue<int> Q;
    Q.push(inds);
    while (!Q.empty()) {
        int a = Q.front(); Q.pop();
        for (int i = 0; i < edges[a].size(); i++) {
            Edge &e = edges[a][i];
            if (e.cap == 0) continue;
            int b = e.end;
            // if not visited
            if (dist[b] == INF) {
                dist[b] = 0;
                parent[b] = a;
                index[b] = i;
                Q.push(b);
            }
        }
    }
    return dist[indt] == 0;
}

bool NFRouter::OK() {
    parent[inds] = -1;
    while (findOnePath()) {
        augment();
    }
    return fulfill();
}
