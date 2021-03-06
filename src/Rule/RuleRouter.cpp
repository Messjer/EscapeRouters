#include "RuleRouter.h"
#include <cmath>
#include <queue>
using namespace std;

const int RuleRouter::dx[5] = {0, -1, 0, 1, 0};

const int RuleRouter::dy[5] = {0, 0, 1, 0, -1};

void RuleRouter::set(int n, int m, int k)
{
  Router::set(n, m, k);
  vector<Point> vec(DM, Point(NOVISITED));
  m_map.assign(DN, vec);

  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      m_map[(i + 1) * (K + 1) - 1][(j + 1) * (K + 1) - 1].status = NOFOUND;
  cost = 0;
  flow = 0;
}

bool RuleRouter::OK()
{
  if(N % 2) {
      if (!odd_search())
          return false;
  } else {
      if (!even_search())
          return false;
  }
  Board* rst = new Board(N, M, K);
  bool ok = rotate(rst);
  delete rst;
  return ok;
}

bool RuleRouter::rotate(Board* rst)
{
  int direct = 0;
  for (int i = 1; i <= (N / 2) * (K + 1); ++i)
    for (int j = Start(i); j <= End(i); ++j)
    {
      direct = m_map[i - 1][j - 1].direct ;
      if(!direct)continue ;
      if(rst->table[i][j] || rst->table[j][DN - i + 1] || rst->table[DN - i + 1][DM - j + 1] || rst->table[DM - j + 1][i])
        return false;
      rst->table[i][j] = direct;
      rst->table[j][DN - i + 1] = turn(direct);
      rst->table[DN - i + 1][DM - j + 1] = turn(direct);
      rst->table[DM - j + 1][i] = turn(direct);
    }
  return true;
}

int RuleRouter::Start(int i)
{
  int j = 1;
  while(!m_map[i-1][j-1].direct)j++;
  return j;

}

int RuleRouter::End(int i)
{
  int j = DM;
  while(!m_map[i-1][j-1].direct)j--;
  return j;
}

Board* RuleRouter::route()
{
  if(N % 2)
  {
    if(!odd_search())
    {
      cout << "can't solve" << endl;
      return NULL;
    }
  }
  else
  {
    if (!even_search())
    {
      cout << "can't solve" << endl;
      return NULL;
    }
  }


  flow *= 4;
  cost *= 4;


  Board* rst = new Board(N, M, K);
  queue<int> q;
  if(N % 2)
  {
    int i = DN / 2 + 1, j = DM / 2 + 1;
    int dir = 0, ni = 0, nj = 0, overcost = 0 ;
    while (i > 0 && i <= DN && j > 0 && j <= DM)
    {
      dir = m_map[i - 1][j - 1].direct;
      ni = i + Board::dy(dir);
      nj = j + Board::dx(dir);
      q.push(dir);
      m_map[i - 1][j - 1].direct = 0 ;
      overcost++;
      i = ni;
      j = nj;
    }
    flow -= 3;
    cost -= 3 * overcost;
  }
  rotate(rst);
  if(N % 2)
  {
    int i = DN / 2 + 1, j = DM / 2 + 1 ;
    int dir;
    while(!q.empty())
    {
      dir = q.front();
      q.pop();
      rst->table[i][j] = dir;
      i += Board::dy(dir);
      j += Board::dx(dir);
    }
  }
  return rst;
}
bool RuleRouter::even_search()
{
  int div_k = K / 2 + 1;
  int middle_n = N / 2 - 1;
  for (int k = 0; k <= middle_n - div_k ; k++)
    search_point((k + 1) * (K + 1) - 1, (middle_n + 1) * (K + 1) -1, Board::UP, Board::LEFT, Board::DOWN);
  for (int k = middle_n; k > middle_n - div_k; k--)
    search_point((k + 1) * (K + 1) - 1, (middle_n + 1) * (K + 1) -1, Board::UP, Board::RIGHT, Board::DOWN);
  for (int j = middle_n - 1; j >= 0; j--)
    for (int i = 0; i < j + 1; i++)
      search_point((i + 1) * (K + 1) - 1, (j + 1) * (K + 1) - 1, Board::UP, Board::LEFT, Board::DOWN);

  div_k = K - div_k;
  for (int k = 0; k <= middle_n - 1 - div_k; k++)
    search_point((k + 1) * (K + 1) - 1, (middle_n + 2) * (K + 1) -1, Board::UP, Board::RIGHT, Board::DOWN);
  for (int k = middle_n - 1; k > middle_n - 1 - div_k; k--)
    search_point((k + 1) * (K + 1) - 1, (middle_n + 2) * (K + 1) -1, Board::UP, Board::LEFT, Board::DOWN);
  for (int j = middle_n + 2; j < N - 1; j++)
    for (int i = 0; i < N - j - 1; i++)
      search_point((i + 1) * (K + 1) - 1, (j + 1) * (K + 1) -1, Board::UP, Board::RIGHT, Board::DOWN);
  if (flow != N * N / 4) return false;
  return true;
}

bool RuleRouter::odd_search()
{
  int middle_n = (N - 1) / 2;
  for (int i = 0; i < K - 1; i++)
    search_point((i + 1) * (K + 1) - 1, (middle_n + 1) * (K + 1) - 1, Board::UP, Board::LEFT, Board::DOWN);
  for (int i = K - 1; i < 2 * K - 1; i++)
    search_point((i + 1) * (K + 1) - 1, (middle_n + 1) * (K + 1) - 1, Board::UP, Board::RIGHT, Board::DOWN);

  for (int i = 2 * K - 1; i <= middle_n; i++)
    search_point((i + 1) * (K + 1) - 1, (middle_n + 1) * (K + 1) - 1, Board::UP, Board::LEFT, Board::DOWN);

  for (int j = middle_n - 1; j >= 0; j--)
    for (int i = 0; i <= j; ++i)
      search_point((i + 1) * (K + 1) - 1, (j + 1) * (K + 1) - 1, Board::UP, Board::LEFT, Board::DOWN);

  for (int j = middle_n + 1; j <= N - 1; j++)
    for (int i = 0; i < N - 1 - j; ++i)
      search_point((i + 1) * (K + 1) - 1, (j + 1) * (K + 1) - 1, Board::UP, Board::RIGHT, Board::DOWN);
  if (flow !=  (N * N - 1) / 4 + 1) return false;
  return true;


}

void RuleRouter::reset()
{
  Router::reset();
}

bool RuleRouter::search_point(int x, int y, int Dir1, int Dir2,int Dir3) {
  if (m_map[x][y].status == VISITED) return false;
    //if (K == 4 && x == 24) {
    //    cout << "FDSJFKLDSJ" << endl;
    //}
  int X = (x + 1) / (K + 1) - 1;
  int Y = (y + 1) / (K + 1) - 1;
  if (Dir2 == Board::LEFT && X > Y) return false;
  if (Dir2 == Board::RIGHT && ((X + Y) >= (N - 1)) && (X != N / 2)) return false;
  bool find = true;
  int newx = x;
  int newy = y;
//  cout << "search " << endl;
  while (find) {
    //  cout << "index: " << newx << " " << newy << endl;
    find = false;
    //Dir1
    int nextx = newx + dx[Dir1];
    int nexty = newy + dy[Dir1];

    if (is_border(nextx, nexty)) {
      find = true;
      m_map[nextx][nexty].pre_direct = Dir1;
      newx = nextx;
      newy = nexty;
      break;
    }

    if (m_map[nextx][nexty].status == NOVISITED) {
      m_map[nextx][nexty].pre_direct = Dir1;
      newx = nextx, newy = nexty;
      find = true;
      continue;
    }

    if (m_map[nextx][nexty].status == NOFOUND)
      if (!search_point(nextx, nexty, Dir1, Dir2, Dir3)) {
        find = false;
        break;
      }

    nextx = newx + dx[Dir2];
    nexty = newy + dy[Dir2];

    if (m_map[nextx][nexty].status == NOVISITED) {
      m_map[nextx][nexty].pre_direct = Dir2;
      newx = nextx, newy = nexty;
      find = true;
      continue;
    }

    if (m_map[nextx][nexty].status == NOFOUND) {
      int prex = newx;
      int prey = newy;
      while (m_map[prex][prey].pre_direct == Dir2) {
        m_map[prex][prey].status = VISITED;
        prex = prex - dx[m_map[prex][prey].pre_direct];
        prey = prey - dy[m_map[prex][prey].pre_direct];
      }
      m_map[prex][prey].status = VISITED;
      prex = prex - dx[m_map[prex][prey].pre_direct];
      prey = prey - dy[m_map[prex][prey].pre_direct];

      newx = prex;
      newy = prey;
      find = true;
    }
  }

  if (find) {
    m_map[newx][newy].direct = m_map[newx][newy].pre_direct;
    while (m_map[newx][newy].status != NOFOUND) {
      //cout << "index: " << newx << " " << newy << " " << m_map[newx][newy].pre_direct << endl;
      m_map[newx][newy].status = VISITED;
      int nextx = newx - dx[m_map[newx][newy].pre_direct];
      int nexty = newy - dy[m_map[newx][newy].pre_direct];
      m_map[nextx][nexty].direct = m_map[newx][newy].pre_direct;
      newx = nextx;
      newy = nexty;
      cost++;
    }
    m_map[newx][newy].status = VISITED;
    flow++;
    cost++;
  } else
    return false;
  return find;
}
