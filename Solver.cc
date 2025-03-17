#include "Solver.h"

const int DIRECTIONS [4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

//функція перевірки поставновки стіни, повинна пришвидшити виконання програми (хоча б по мінімуму)
static bool canWallify(Grid *grid, int x, int y) {
    for (auto [x, y]: grid->visibleValues(x, y)) {
        if (grid->countVisible(x, y) <= grid->grid[x][y].value) {
            return false;
        }
    }
    return true;
}

//Функція для валідації чи є розв'язок вірним. Просто ітерує усі елементи та перевіряє, чи точки з числами бачать вірну кількість.
static bool validateNumbers(Grid *grid) {
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

//Функція яка з'єднує стіни до кордонів гріда
static bool connectWall(Grid *grid, int x, int y) {
    if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return false;
    }

    if (grid->grid[x][y].type == CONFIRMED_WALL) {
        return true;
    }

    if (grid->grid[x][y].type != WALL) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        int move_x = x + DIRECTIONS[i][0];
        int move_y = y + DIRECTIONS[i][1];
        if((move_x < 0 || move_x >= grid->width) || (move_y < 0 || move_y >= grid->height)){
            grid->grid[x][y].type = CONFIRMED_WALL;
            continue;
        }
        if (grid->grid[move_x][move_y].type == WALL) {
            if (connectWall(grid, move_x, move_y)) {
                grid->grid[x][y].type = CONFIRMED_WALL;
            }
        } else if (grid->grid[move_x][move_y].type == CONFIRMED_WALL && grid->grid[x][y].type != CONFIRMED_WALL) {
            grid->grid[x][y].type = CONFIRMED_WALL;
        } else if (grid->grid[move_x][move_y].type == CELL) {
            if (canWallify(grid, move_x, move_y)) {
                grid->grid[move_x][move_y].wallify();
                if (!connectWall(grid, move_x, move_y)) {
                    grid->grid[move_x][move_y].cellify();
                } else if (grid->grid[move_x][move_y].type == CONFIRMED_WALL) {
                    grid->grid[x][y].type = CONFIRMED_WALL;
                }
            }
        }
    }
    return grid->grid[x][y].type == CONFIRMED_WALL;
}

static bool validateWalls(Grid *grid) {
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->grid[x][y].type == WALL && !connectWall(grid, x, y)) {
                return false;
            } 
        }
    }
    return true;
}


//Функція що зазово замальовує клітинки
static bool fillWalls(Grid *grid, int x, int y) {
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
        return fillWalls(grid, next_x, next_y);
    }

    if (canWallify(grid, x, y)) {
        grid->grid[x][y].wallify();
        if (grid->fullyConnected() && (validateNumbers(grid) || fillWalls(grid, next_x, next_y))) {
            return true;
        }
    }

    grid->grid[x][y].cellify();
    if (validateNumbers(grid) || fillWalls(grid, next_x, next_y)) {
        return true;
    }

    return false; //Не знайдено розв'язків
}

//Функція яка розв'язує саму головоломку. 
bool solveCave(Grid *grid) {
    return fillWalls(grid, 0, 0) && validateWalls(grid);
}
