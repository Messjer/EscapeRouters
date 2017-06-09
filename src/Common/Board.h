#ifndef SRC_BOARD_H
#define SRC_BOARD_H
#include <iostream>
#include <cstring>
#include <cassert>

class Board {
public:
    static const int MAX_BOARD_SIZE = 300;
    /// N * M board, with K routing lines in between
    /// assume N <= M
    int N, M, K;

    /// dimension of the vertices
    int DN, DM;

    /// internal variables for directions
    enum Directions {
        NO_MOVE,
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        LEFT = 4
    };

    static const int dx(int index) {
        static const int dx[5] = {0, 0, 1, 0, -1};
        return dx[index];
    }

    static const int dy(int index) {
        static const int dy[5] = {0, -1, 0, 1, 0};
        return dy[index];
    }

    /// edge table, store directions of the edges starting from
    /// position (i, j)
    int table[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    /// Construct a board with given dimension
    /// @param height of the board
    /// @param width of the board
    /// @param routing line in between
    /// @assume N <= M
    Board(int n, int m, int k) : N(n), M(m), K(k), DN(n * (k + 1) + k), DM(m * (k + 1) + k) {
        assert(DN <= MAX_BOARD_SIZE && DM <= MAX_BOARD_SIZE);
        memset(table, 0, sizeof(table));
    }

    friend std::ostream& operator<<(std::ostream &out, const Board &b);
};

#endif //SRC_BOARD_H
