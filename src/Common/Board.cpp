#include "Board.h"
using namespace std;

std::ostream& operator << (std::ostream &out, const Board &b) {
    out << b.N << ' ' << b.M << ' ' << b.K << endl;
    for (int i = 1; i <= b.DN; i++, out << endl)
        for (int j = 1; j <= b.DM; j++)
            out << b.table[i][j] << ' ';
    return out;
}