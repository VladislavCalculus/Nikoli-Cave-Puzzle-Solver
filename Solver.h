#ifndef SOLVER_H
#define SOLVER_H

#include "Grid.h"
using namespace std;

//Клас солвера для розв'язання самої головомки
class Solver {
    Solver(Grid *grid);
    void Solve();

private:
    Grid *grid;
    bool validateSolution();
};

#endif