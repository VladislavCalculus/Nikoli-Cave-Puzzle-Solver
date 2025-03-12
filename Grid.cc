#include <iostream>
#include <unordered_set>
#include "Grid.h"

using namespace std;

const int directions [4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // Напрямки: вправо, вниз, вліво, вгору

// Конструктор класу.
Grid::Grid(int w, int h) {
    width = w;
    height = h;
    grid.resize(width, vector<Point>(height));
}

// Встановлення точки.
void Grid::setPoint(int x, int y, Point p) {
    if (x < width && y < height) {
        grid[x][y] = p;
    }
}

// Вивід поля.
void Grid::show() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            cout << grid[x][y].str;
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
            int move_x = x + directions[i][0] * cursor;
            int move_y = y + directions[i][1] * cursor;
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

//Функція для підрахунку кількості пустих клітинок. Використовується в перевірці цілісності поля.
int Grid::countCaveCells() {
    int counter = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type != WALL) {
                counter++;
            }
        }
    }
    return counter;
}

//Функція для перевірки цілісності поля.
bool Grid::fullyConnected(){
    vector<pair<int, int>> move_to; //Вектор який буде наповнюватися можливими варіантами для руху щоб запобігнути повторним мувам.
    for (int x = 0; x < width; x++) { //Пошук стартової клітинки. (Можливо варто буде оптимізувати)
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type != WALL) {
                move_to.push_back({x, y});
                break;
            }
        }
        if (!move_to.empty()) {
            break;
        }
    }
    if (move_to.empty()) { //Не знайдена ні одна пуста клітинка.
        return false;
    }

    unordered_set<Point*> visited; 
    while (!move_to.empty()) {
        auto [x, y] = move_to.back(); //Отримання певного елемента
        //+P.S. - auto для того щоб не визначати тип самому, а [x, y] - річ доступна для отримання змінних з класу, починаючи з С++17 (Structured bilding declaration)
        move_to.pop_back(); //Забирання цього елементу зі списку
        Point* curr_point = &grid[x][y];
        if (!visited.insert(curr_point).second) { //Перевірка є вже об'єкт в відвіданих
            continue;
        }
    }


    //Кінцівка
    return visited.size() == countCaveCells();
}