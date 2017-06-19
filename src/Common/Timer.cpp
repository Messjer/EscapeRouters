#include "Timer.h"
#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Timer::timedTest(Solver::RouterType type)
{
    string rt;
    if (type == Solver::NF) rt = "NF";
    else if (type == Solver::DC) rt = "DC";
    else if (type == Solver::RU) rt = "RU";
    if (type != Solver::NF && m != n) {
        cout <<"DC & RU Router can only solve squares" <<endl;
        return;
    }

    cout <<"Timing on " <<m <<" by " <<n <<" type is " <<rt <<endl <<endl;

    long start = clock();
    Solver s;
    Board* b = s.solve(m, n, type);

    double elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
    printf("Used %.5lf secs to route.\n\n", elapsed);

    string dir = "../../testcase/";
    stringstream ss;

    dir += rt + '/';
    ss <<dir <<"solution" <<m <<"by" <<n <<".txt";

    std::ofstream fout(ss.str());
    if(b)
    {
        fout << (*b) << std::endl;
        delete b;
    } else
        cout <<"Something Wrong!!!" <<endl;
    fout.close();

    stringstream ss2;
    ss2 <<dir;
    ss2 <<"stats" <<m <<"by" <<n <<".csv";
    std::ofstream statout(ss2.str());
    statout <<"M, N, Gap Size, Flow, Length, Time(s)" <<endl;
    statout <<m <<',' <<n <<',' <<b -> K <<',' <<s.flow <<',' <<s.cost <<',' <<elapsed <<endl;
	statout.close();
}
