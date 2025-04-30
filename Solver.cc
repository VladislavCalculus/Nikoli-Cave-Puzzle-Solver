#include "Solver.h"
#include <unordered_set>

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
static bool connectWall(Grid *grid, int x, int y, unordered_set<Point*> &visited) {
    if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return false;
    }

    Point *curr = &grid->grid[x][y];
    //cout << "X: " << x << " | Y: " << y << " | TYPE: " << grid->grid[x][y].type << endl;
    if (curr->type == CONFIRMED_WALL) {
        return true;
    } else if (curr->type != WALL) {
        return false;
    } 
    if (!visited.insert(curr).second) { 
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int move_x = x + DIRECTIONS[i][0];
        int move_y = y + DIRECTIONS[i][1];
        if(move_x < 0 || move_x >= grid->width || move_y < 0 || move_y >= grid->height){
            curr->type = CONFIRMED_WALL;
            return true;
        }
        Point *next = &grid->grid[move_x][move_y];
        if (next->type == CONFIRMED_WALL) {
            curr->type = CONFIRMED_WALL;
            return true;
        } else if (next->type == WALL) {
            if (connectWall(grid, move_x, move_y, visited)) {
                curr->type = CONFIRMED_WALL;
                return true;
            }
        } else if (next->type == CELL) {
            if (canWallify(grid, move_x, move_y)) {
                cout << "This cell can be wallified | X: " << move_x << " | Y: "<< move_y << endl;
                next->wallify();
                if (grid->fullyConnected() && connectWall(grid, move_x, move_y, visited)) {
                    curr->type = CONFIRMED_WALL;
                    return true;
                } else {
                    next->cellify();
                }
            }
        }
    }
    return false;
}

static bool validateWalls(Grid *grid, unordered_set<Point*> &visited) {
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->grid[x][y].type == WALL && !connectWall(grid, x, y, visited)) {
                return false;
            } 
        }
    }
    return true;
}

//Функція що замальовує клітинки
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
    unordered_set<Point*> visited; 
    return fillWalls(grid, 0, 0) && validateWalls(grid, visited);
}

//Для руху по спіралі використаємо цю функцію. Вона буде знаходити наступний крок. loop - це зміна вказує поточне кільце.
static pair<int, int> nextSpiralMove(Grid *grid, int x, int y, int &loop) {
    int maxLoops = min(grid->width, grid->height) / 2 + (min(grid->width, grid->height) % 2 != 0) + 1;
    if (loop > maxLoops) {
        return {-1, -1}; // Вихід за межі
    }

    if(y == loop+1 && x == loop) {
        loop++;
        return {loop, loop};
    }

    // Праворуч
    if (y == loop && x < grid->width - loop - 1) {
        return {x + 1, y};
    }

    // Вниз
    if (x == grid->width - loop - 1 && y < grid->height - loop - 1) {
        return {x, y + 1};
    }

    // Ліворуч
    if (y == grid->height - loop - 1 && x > loop) {
        return {x - 1, y};
    }

    // Вгору
    if (x == loop && y > loop) {
        return {x, y - 1};
    }

    return {-1, -1};
}

static bool checkWall(Grid *grid, int x, int y, unordered_set<Point*> &visited) {
    if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
        return false;
    }

    Point *curr = &grid->grid[x][y];
    if (curr->type == CONFIRMED_WALL) {
        return true;
    } else if (curr->type != WALL) {
        return false;
    } 
    if (!visited.insert(curr).second) { 
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int move_x = x + DIRECTIONS[i][0];
        int move_y = y + DIRECTIONS[i][1];
        if(move_x < 0 || move_x >= grid->width || move_y < 0 || move_y >= grid->height){
            curr->type = CONFIRMED_WALL;
            return true;
        }
        Point *next = &grid->grid[move_x][move_y];
        if (next->type == CONFIRMED_WALL) {
            curr->type = CONFIRMED_WALL;
            return true;
        } else if (next->type == WALL) {
            if (connectWall(grid, move_x, move_y, visited)) {
                curr->type = CONFIRMED_WALL;
                return true;
            }
        }
    }
    return false;
}

static bool checkWallConnectivity(Grid *grid) {
    for(int x = 0; x < grid->width; x++) {
        for(int y = 0; y < grid->height; y++) {
            if(grid->grid[x][y].type == CONFIRMED_WALL) {
                grid->grid[x][y].type = WALL;
            }
        }
    }


    unordered_set<Point*> visited;
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->grid[x][y].type == WALL && !checkWall(grid, x, y, visited)) {
                return false;
            } 
        }
    }
    return true;
}

//Функція яка дозволяє користувачеві розв'зязувати головомку. 
bool solveCaveUser(Grid *grid) {
    cout << "\n" << endl;
    cout << "How to use:\nenter 2 numbers (separeted by space) - change the state of the cell (Route -> Wall and wise-versa)\nenter -1 -1 - exit solving\n" << endl;
    cout << "WARNING! Cell counting starts with 0, be aware of that.\n" << endl;

    while (true) {
        grid->show();

        int x, y = -1;
        cout << "enter coordinates: ";
        cin >> y >> x;

        //вихід з програми
        if (x == -1 || y == -1) {
            break;
        }

        //перевірка чи координати правильні
        if (x >= grid->width || y >= grid->height || x < 0 || y < 0) {
            cout << "Invalid coordinates.\n" << endl;
            continue;
        }

        //перевірка чи точка не є з номером
        if (grid->grid[x][y].type == VALUED_CELL) {
            cout << "This cell is valued, can't change it.\n" << endl;
            continue;
        }

        //зміна стану точки
        if (grid->grid[x][y].type == CELL) {
            if (canWallify(grid, x, y)) {
                grid->grid[x][y].wallify();
                if(!grid->fullyConnected()) {
                    grid->grid[x][y].cellify();
                    cout << "This cell can't be a wall because it ruins the loop of the grid cells\n";
                    continue;
                }
            } else {
                cout << "This cell can't be a wall because valued cell will see less than it should be seeing.\n";
                continue;
            }
        } else {
            grid->grid[x][y].cellify();
        }

        //якщо поле заповнено правильно - виходимо
        if (validateNumbers(grid) && checkWallConnectivity(grid)) { 
            cout << "Solved!\n" << endl;
            return true;
        }

        cout << "\n";
    }
    return false;
}