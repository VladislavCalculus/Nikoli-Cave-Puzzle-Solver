#ifndef GRID_H
#define GRID_H

#include "Point.h"
#include <vector>
using namespace std;

extern int g_directions[4][2];

struct Grid {
    vector<vector<Point>> grid;
    int width, height;

    Grid(int w, int h);
    void setPoint(int x, int y, Point p);
    void show();
    int countVisible(int x, int y);
};

#endif