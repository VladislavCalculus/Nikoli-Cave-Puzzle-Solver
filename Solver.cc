#include "Solver.h"
using namespace std;

//TODO: Функція яка розв'язує саму головоломку.
void solveCave(Grid *grid) {
    return;
}

//TODO: Функція для валідації чи є розв'язок вірним. Просто ітерує усі елементи та перевіряє, чи точки з числами бачать вірну кількість.
bool validateSolution(Grid *grid) {
    if (!grid->fullyConnected()) { //Можливо варто буде видалити цю перевірку пізніше, адже вона буде виконуватися в солвері.
        return false;
    }
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->grid[x][y].type != VALUED_CELL){
                continue;
            } else if(grid->grid[x][y].value != grid->countVisible(x, y)) {
                return false;
            }
        }
    }
    return true;
}
