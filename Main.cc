#include <iostream>
#include "Grid.h"


using namespace std;

int main() {
    Grid grid(7, 7);
    
    grid.setPoint(0, 2, Point(5));
    grid.setPoint(0, 4, Point(2));

    grid.setPoint(1, 1, Point(3));
    grid.setPoint(1, 5, Point(3));

    grid.setPoint(2, 0, Point(2));
    grid.setPoint(2, 2, Point(9));
    grid.setPoint(2, 4, Point(5));
    grid.setPoint(2, 6, Point(5));

    grid.setPoint(3, 3, Point(4));
    grid.setPoint(3, 4, Point());
    grid.grid[3][4].wallify();

    grid.setPoint(4, 0, Point(8));
    grid.setPoint(4, 2, Point(11));
    grid.setPoint(4, 4, Point(7));
    grid.setPoint(4, 6, Point(8));

    grid.setPoint(5, 1, Point(4));
    grid.setPoint(5, 5, Point(4));

    grid.setPoint(6, 2, Point(2));
    grid.setPoint(6, 4, Point(2));

    cout << "Grid state:\n";
    grid.show();

    cout << grid.countVisible(3, 3);

    return 0;
}