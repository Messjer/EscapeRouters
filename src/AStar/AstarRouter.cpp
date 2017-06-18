#include "AstarRouter.h"

using namespace std;

void AStarRouter::set(int n, int m, int k)
{
    Router::set(n, m, k);
    vector<Point> vec(DM, Point());
    map.assign(DN, vec);
    for (int i = 0; i < DN; i++)
        for (int j = 0; j < DM; j++)
        {
            map[i][j].status = NOVISITED;
            map[i][j].index = getIndex(i, j);
            map[i][j].cost = 0;
            map[i][j].direct = Board::NO_MOVE;
            map[i][j].pre_direct = Board::NO_MOVE;
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            map[(i + 1) * (k + 1) - 1][(j + 1) * (k + 1) -1].status = CLOSED;
    cost = 0;
    flow = 0;
}

void AStarRouter::reset() {
    Router::reset();
}

Board* AStarRouter::route()
{
    round_search(0);

    Board *rst = new Board(N, M, K);

    for (int i = 1; i <= DN; i++)
        for (int j = 1; j <= DM; j++)
            rst->table[i][j] = map[i - 1][j - 1].direct;
    return rst;
}

void AStarRouter::round_search(int k)
{
    if ((k >= N / 2) && (N % 2 == 0)) return;
    if ((k >= N / 2) && (N % 2 == 1))
    {
      find_route((k + 1) * (K + 1) - 1, (k + 1) * (K + 1) - 1, Board::UP);
      return;
    }
    for (int i = k; i < N - k - 1; ++i)
        find_route((i + 1) * (K + 1) -1, (k + 1) * (K + 1) - 1, Board::LEFT);
    for (int i = k; i < N - k - 1; ++i)
        find_route((N - k) * (K + 1) - 1, (i + 1) * (K + 1) - 1, Board::DOWN);
    for (int i = k + 1; i < N - k; i++)
        find_route((i + 1) * (K + 1) - 1, (N - k) * (K + 1) - 1, Board::RIGHT);
    for (int i = k + 1; i < N - k; i ++)
        find_route((k + 1) * (K + 1) - 1, (i + 1)* (K + 1) - 1, Board::UP);

    round_search(k + 1);
    return;
}

void AStarRouter::find_route(int x, int y, int Dir)
{
    openList.clear();
    closeList.clear();
    openList.push_back(map[x][y].index);
    // cout << endl;

    while (openList.size() != 0)
    {
        int minIndex;
        find_minPoint(minIndex);
        bool find = false;

        int x, y;
        getXY(minIndex, x, y);
        // cout <<"index: " << x << " " << y << endl;
        closeList.push_back(map[x][y].index);
        for (int dir = Board::UP; dir <= Board::LEFT; dir++)
        {
            int newx = x + dx[dir], newy = y + dy[dir];
            if (!valid(newx, newy) || map[newx][newy].status == CLOSED) continue;
            auto it = std::find(closeList.begin(), closeList.end(), getIndex(newx, newy));
            if ( it != closeList.end() ) continue;
            if (std::find(openList.begin(), openList.end(), getIndex(newx, newy)) != openList.end())
            {
                if (map[newx][newy]. expect_value > map[x][y].expect_value + 1)
                {
                    map[newx][newy].cost = map[x][y].cost + 1;
                    map[newx][newy].expect_value = map[newx][newy].cost + map[newx][newy].G;
                    map[newx][newy].pre_direct = dir;
                }
            }
            else{
                map[newx][newy].cost = map[x][y].cost + 1;
                cal_expect_cost(map[newx][newy], Dir);
                map[newx][newy].pre_direct = dir;
                openList.push_back(map[newx][newy].index);
                // cout << map[newx][newy].index << endl;
                // cout << map[newx][newy].expect_cost[Min] << endl;
                // cout << map[newx][newy].expect_value << endl;
                // cout << newx << "  " << newy << endl;

                if (newx == 0 || newy == 0 || newx == DN - 1 || newy == DM - 1)
                {
                    map[newx][newy].direct = map[newx][newy].pre_direct;
                    map[newx][newy].status = CLOSED;
                    set_direct(x, y, map[newx][newy].pre_direct);
                    cost = map[newx][newy].cost  + cost + 1;
                    //    cout << "gg" << endl;
                    find = true;
                    flow++;
                    break;
                }
            }
        }
        if (find) {
            for (auto j : openList)
            {
                clean(j);
            }
            break;
        }
    }
}

void AStarRouter::cal_expect_cost(Point &p, int Dir)
{
    int x, y;
    getXY(p.index, x, y);
    p.expect_cost[Xs] = min(x, DN - x - 1);
    p.expect_cost[Ys]= min(y, DM - y - 1);

    p.expect_cost[Min] = min(p.expect_cost[Xs], p.expect_cost[Ys]);
  /*  p.expect_cost[Max] = p.expect_cost[Xs] + p.expect_cost[Ys] - p.expect_cost[Min];*/

    if (Dir == Board::UP || Dir == Board::DOWN) p.G = p.expect_cost[Xs] * 2 + p.expect_cost[Ys];
    else p.G = p.expect_cost[Xs] + p.expect_cost[Ys] * 2;

    p.expect_value = p.cost + p.G;
}

void AStarRouter::set_direct(int x, int y, int pre_direct)
{
    map[x][y].status = CLOSED;
    if (map[x][y].pre_direct == Board::NO_MOVE)
    {
//    cout << "now: " <<  x << " " << y << endl;
        map[x][y].direct = pre_direct;
        return;
    }
//  cout << "g" << endl;
    map[x][y].direct = pre_direct;
    int newx = x - dx[map[x][y].pre_direct];
    int newy = y - dy[map[x][y].pre_direct];
//  cout << newx << " " << newy << endl;
    set_direct(newx, newy, map[x][y].pre_direct);
}

void AStarRouter::find_minPoint(int &minIndex)
{
    minIndex = 0;
    Point p;
    p.expect_value = 1000000;
    vector<int>::iterator it;
    for (auto i = openList.begin(); i < openList.end(); i++)
    {
        int x,y;
        getXY(*i, x, y);
        if (p.expect_value > map[x][y].expect_value)
        {
            p = map[x][y];
            it = i;
        }
        else if (p.expect_value == map[x][y].expect_value)
        {
            if (p.expect_cost[Min] > map[x][y].expect_cost[Min])
                p = map[x][y], it = i;
        }
    }
    minIndex = p.index;
    openList.erase(it);
    // cout << "min point:" << minIndex << endl;
    return;
}

void AStarRouter::clean(int index)
{
    int x, y;
    getXY(index, x, y);
    map[x][y].cost = 0;
}
