//
// Created by Hong Man Hou on 7/6/2017.
//
#include "NFRouter.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    NFRouter router(20, 30, 7);
    Board *b = router.route();
    ofstream fout("solution.txt");
    if (b) {
        fout << (*b) << endl;
        // router.print_status();
        delete b;
    }
    return 0;
}