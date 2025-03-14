#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "Grid.h"
using namespace std;

extern bool solveCave (Grid *grid, int x, int y);
extern bool validateSolution (Grid *grid);

#endif