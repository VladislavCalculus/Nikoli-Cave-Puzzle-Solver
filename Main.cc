#include <iostream>
#include "Solver.h"

using namespace std;

int main() {
    //TODO: Імплементувати повноцінний файл інтерфейсу
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
    grid.setPoint(4, 0, Point(8));
    grid.setPoint(4, 2, Point(11));
    grid.setPoint(4, 4, Point(7));
    grid.setPoint(4, 6, Point(8));
    grid.setPoint(5, 1, Point(4));
    grid.setPoint(5, 5, Point(4));
    grid.setPoint(6, 2, Point(2));
    grid.setPoint(6, 4, Point(2));

    grid.grid[0][0].wallify();
    grid.grid[0][1].wallify();
    grid.grid[0][3].wallify();
    grid.grid[0][6].wallify();
    grid.grid[1][3].wallify();
    grid.grid[1][4].wallify();
    grid.grid[1][6].wallify();
    grid.grid[2][1].wallify();
    grid.grid[3][0].wallify();
    grid.grid[3][1].wallify();
    grid.grid[3][4].wallify();
    grid.grid[3][5].wallify();
    grid.grid[3][6].wallify();
    grid.grid[5][2].wallify();
    grid.grid[5][3].wallify();
    grid.grid[5][4].wallify();
    grid.grid[6][0].wallify();
    grid.grid[6][3].wallify();
    grid.grid[6][6].wallify();

    cout << "Grid state:\n";
    grid.show();

    

    return 0;
}