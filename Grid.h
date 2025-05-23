#ifndef GRID_H
#define GRID_H

#include "Point.h"
#include <vector>
#include <queue>
using namespace std;

struct Grid {
    vector<vector<Point>> grid;
    int width, height;

    Grid(int w, int h);
    void setPoint(int x, int y, Point p);
    void show();
    int countVisible(int x, int y);
    vector<pair<int, int>> visibleValues(int x, int y);
    bool fullyConnected();
private:
    size_t countCaveCells();
    bool canMoveTo(int x, int y, int direction, int distance);
    void findStart(queue<pair<int, int>> &move_to);
};

#endif