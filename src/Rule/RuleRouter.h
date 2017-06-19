#ifndef RULEROUTER_H
#define RULEROUTER_H

#include "../Common/Router.h"
#include <vector>

class RuleRouter: public Router
{
public:
    enum Status {
        VISITED = 0,
        NOVISITED,
        NOFOUND,
    };

    struct Point
    {
        int status;
        int direct;
        int pre_direct;

        Point(int s) : status(s), direct(0), pre_direct(0) {}
    };

    static const int dx[5];

    static const int dy[5];

private:
    std::vector<std::vector<Point>> m_map;
    std::vector<int> m_right, m_up, m_down, m_left; //count

public:
    void set(int n, int m, int k);

    Board* route();
    void reset();
    bool search_point(int x, int y, int Dir1, int Dir2, int Dir3);
    bool even_search();
    bool odd_search();

    bool OK();

    bool is_border(int x, int y)
    {
      return (x == 0 || x == DN - 1 || y == 0 || y == DM - 1);
    }

    void print_status() {
      for (int i = 0; i < DN; i++)
      {
        for (int j = 0; j < DM; j++)
          std::cout << m_map[i][j].status << " ";
        std::cout << std::endl;
      }
    }
private:
    bool rotate(Board*);
    int turn(int& dir)
    {
      dir = (dir)? dir % 4 + 1 : 0;
      return dir;
    }
    int Start(int);
    int End(int);
};

#endif
