#include <iostream>
#include "Grid.h"

using namespace std;

int g_directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // Напрямки: вправо, вниз, вліво, вгору

// Конструктор класу.
Grid::Grid(int w, int h) {
    width = w;
    height = h;
    grid.resize(width, vector<Point>(height));
}

// Встановлення точки.
void Grid::setPoint(int x, int y, Point p) {
    if (x < width && y < height)
        grid[x][y] = p;
}

// Вивід поля.
void Grid::show() {
    for (auto &row : grid) {
        for (auto &cell : row) {
            cout << cell.str;
        }
        cout << endl;
    }
}

// Функція підрахування видимих точок.
int Grid::countVisible(int x, int y) {
    if (grid[x][y].type != VALUED_CELL) {
        return -1;
    }
    int counter = 1;
    for (int i = 0; i < 4; i++) {
        int cursor = 1;
        while (true) {
            int move_x = x + g_directions[i][0] * cursor;
            int move_y = y + g_directions[i][1] * cursor;
            if ((move_x >= 0 && move_x < width) && (move_y >= 0 && move_y < height) && grid[move_x][move_y].type != WALL) {
                counter++;
                cursor++;
            } else {
                break;
            }
        }
    }
    return counter;
}