#include <iostream>
#include <unordered_set>
#include <queue>
#include "Grid.h"

using namespace std;

const int DIRECTIONS [4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // Напрямки: вправо, вниз, вліво, вгору

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

//Допоміжна прайват функція для перевірки чи з певнох координати можна порухатися. Приймає координати, напрям (від 0 до 3 відповідно) та дистанцію точки від х,у для перевірки.
bool Grid::canMoveTo (int x, int y, int direction, int distance) {
    int move_x = x + DIRECTIONS[direction][0] * distance;
    int move_y = y + DIRECTIONS[direction][1] * distance;
    if ((move_x >= 0 && move_x < width) && (move_y >= 0 && move_y < height) && grid[move_x][move_y].type != WALL) {
            return true;
    }
    return false;
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
            if (canMoveTo(x, y, i, cursor)) {
                counter++;
                cursor++;
            } else {
                break;
            }
        }
    }
    return counter;
}

vector<pair<int, int>> Grid::visibleValues(int x, int y){
    vector<pair<int, int>> visible;
    for(int i = 0; i < 4; i++){
        int cursor = 1;
        while (true) {
            if (canMoveTo(x, y, i, cursor)) {
                int move_x = x + DIRECTIONS[i][0] * cursor;
                int move_y = y + DIRECTIONS[i][1] * cursor;
                if (grid[move_x][move_y].type == VALUED_CELL) {
                    visible.push_back(make_pair(move_x, move_y));
                }
                cursor++;
            } else {
                break;
            }
        }
    } 
    return visible;
}

//Функція для підрахунку кількості пустих клітинок. Використовується в перевірці цілісності поля.
size_t Grid::countCaveCells() {
    size_t counter = 0;
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
    queue<pair<int, int>> move_to; //К'ю який буде наповнюватися можливими варіантами для руху щоб запобігнути повторним мувам.
    for (int x = 0; x < width; x++) { //Пошук стартової клітинки. (Можливо варто буде оптимізувати)
        for (int y = 0; y < height; y++) {
            if (grid[x][y].type != WALL) {
                move_to.push({x, y});
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
        auto [x, y] = move_to.front(); //Отримання певного елемента
        //+P.S. - auto для того щоб не визначати тип самому, а [x, y] - річ доступна для отримання змінних з класу, починаючи з С++17 (Structured bilding declaration)
        move_to.pop(); //Забирання цього елементу зі списку
        Point* curr_point = &grid[x][y];
        if (!visited.insert(curr_point).second) { //Перевірка чи є вже об'єкт в відвіданих
            continue;
        }
        for (int i = 0; i < 4; i++) {
            if (canMoveTo(x, y, i, 1)) {
                move_to.push(make_pair(x + DIRECTIONS[i][0], y + DIRECTIONS[i][1]));
            }
        }
    }
    //Кінцівка
    return visited.size() == countCaveCells();
}