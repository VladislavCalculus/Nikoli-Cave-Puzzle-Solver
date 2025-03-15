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



    cout << "Grid state:\n";
    grid.show();

    if (solveCave(&grid, 0, 0)) {
        cout << "\nSolved Grid:\n";
        grid.show();
    } else {
        cout << "\nNo solution found!\n";
    }
    return 0;
}