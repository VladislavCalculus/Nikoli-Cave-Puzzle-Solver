#ifndef GRID_H
#define GRID_H

#include "Point.h"
#include <vector>
using namespace std;

struct Grid {
    vector<vector<Point>> grid;
    int width, height;

    Grid(int w, int h);
    void setPoint(int x, int y, Point p);
    void show();
    int countVisible(int x, int y);
    bool fullyConnected();
private:
    int countCaveCells();
};

#endif