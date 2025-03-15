#include "Solver.h"
using namespace std;

//TODO: функція перевірки поставновки стіни, повинна пришвидшити виконання програми (хоча б по мінімуму)
static bool canWallify(Grid *grid, int x, int y) {
    for (auto [x, y]: grid->visibleValues(x, y)) {
        if (grid->countVisible(x, y) <= grid->grid[x][y].value) {
            return false;
        }
    }
    return true;
}

//Функція для валідації чи є розв'язок вірним. Просто ітерує усі елементи та перевіряє, чи точки з числами бачать вірну кількість.
static bool validateSolution(Grid *grid) {
    if (!grid->fullyConnected()) {
        return false;
    }
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->grid[x][y].type != VALUED_CELL) {
                continue;
            } else if(grid->grid[x][y].value != grid->countVisible(x, y)) {
                return false;
            }
        }
    }
    return true;
}

//TODO: Функція яка розв'язує саму головоломку.
bool solveCave(Grid *grid, int x, int y) {
    if(y >= grid->height){
        return false;
    }
    //cout << "X: " << x << " | Y: " << y << " | str: " << grid->grid[x][y].str << endl;
    int next_x = x;
    int next_y = y;
    if (x < grid->width-1) {
        next_x++;
    } else {
        next_x = 0;
        next_y++;
    }
    if (grid->grid[x][y].type == VALUED_CELL) {
        return solveCave(grid, next_x, next_y);
    }

    if (canWallify(grid, x, y)) {
        grid->grid[x][y].wallify();
        if (validateSolution(grid) || solveCave(grid, next_x, next_y)) {
            return true;
        }
    }

    grid->grid[x][y].cellify();
    if (validateSolution(grid) || solveCave(grid, next_x, next_y)) {
        return true;
    }

    return false; //Не знайдено розв'язків
}