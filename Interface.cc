#include "Interface.h"
#include <string.h>
#include <stdlib.h>

 //Допоміжна ф-ція за допомогою якої виконується перевірка правильності вводу
static int countSpaces(char *line) {
    int counter = 0;
    while (*line) {
        if (*line == ' ') {
            counter++;
        }
        line++;
    }
    return counter;
}

//Функція вводу поля
static Grid enterGrid() {
    int width, height;

    cout << "Enter size of the grid: ";
    cin >> width >> height;

    Grid grid(width, height);
    cin.ignore(); //<- цей ігнор потрібен щоб очистити данні з минулого cin

    cout << "Enter rows for the grid (separate numbers using space):\nExample: 3 0 0 2 0\n0 - blank cell\nDigit - numbered cell\n";
    for (int i = 0; i < width; i++) {
        char line[255];
        cin.getline(line, 255);
        if (countSpaces(line) != width-1) { //За допомогою кількості пробілів перевіряю чи вірна кількість елементів введена, якщо ні - користувач має переввести ввід
            cout << "Invalid input. Reinput row:" << endl;
            i--;
            continue;
        }

        //Внесення точок на поле
        char *token = strtok(line, " ");
        for (int j = 0; j < height && token != nullptr; j++) {
            int num = atoi(token);
            if (num > 0) { //Робимо визначення точки онлі коли в нас число більше 0, адже користувач як 0 вводить пусту клітинку.
                grid.setPoint(i, j, Point(num));
            }
            token = strtok(nullptr, " ");
        }
    }

    return grid;
}

//допоміжна функція для інтефейсу для отримання заготовлених полів.
static Grid chooseGridTemplates() {
    Grid grid1(7, 7);
    grid1.setPoint(0, 2, Point(5));
    grid1.setPoint(0, 4, Point(2));
    grid1.setPoint(1, 1, Point(3));
    grid1.setPoint(1, 5, Point(3));
    grid1.setPoint(2, 0, Point(2));
    grid1.setPoint(2, 2, Point(9));
    grid1.setPoint(2, 4, Point(5));
    grid1.setPoint(2, 6, Point(5));
    grid1.setPoint(3, 3, Point(4));
    grid1.setPoint(4, 0, Point(8));
    grid1.setPoint(4, 2, Point(11));
    grid1.setPoint(4, 4, Point(7));
    grid1.setPoint(4, 6, Point(8));
    grid1.setPoint(5, 1, Point(4));
    grid1.setPoint(5, 5, Point(4));
    grid1.setPoint(6, 2, Point(2));
    grid1.setPoint(6, 4, Point(2));
    Grid grid2(7, 7);
    grid2.setPoint(0, 0, Point(2));
    grid2.setPoint(0, 6, Point(2));
    grid2.setPoint(1, 2, Point(2));
    grid2.setPoint(1, 4, Point(2));
    grid2.setPoint(2, 0, Point(2));
    grid2.setPoint(3, 2, Point(2));
    grid2.setPoint(4, 0, Point(2));
    grid2.setPoint(4, 4, Point(2));
    grid2.setPoint(6, 0, Point(2));
    grid2.setPoint(6, 3, Point(2));
    grid2.setPoint(6, 5, Point(2));
    Grid grid3(3, 3);
    grid3.setPoint(1, 1, Point(3));
    grid3.setPoint(2, 2, Point(2));

    vector<Grid> grids;
    grids.push_back(grid1);
    grids.push_back(grid2);
    grids.push_back(grid3);
    cout << "Templates:" << endl;
    for(size_t i = 0; i < grids.size(); i++) {
        cout << "Template №:" << (i+1) << endl;
        grids[i].show();
        cout << "\n";
    }

    cout << "Enter your option: ";
    size_t option;
    cin >> option;

    option--;
    if (option >= 0 && option < grids.size()) {
        return grids[option];
    } else {
        throw std::invalid_argument("Incorrect template id.");
    }
}

//Функція яка буде визиватися в мейні (Запуск)
void init(){
    cout << "The program solve 'Cave Puzzle' by Nikoli." << endl;

    while (true) {
        cout << "1 - enter yourself\n2 - prewriten templates\n3 - exit\nEnter your option: ";
        int option;
        cin >> option;
        cin.ignore();

        Grid grid(1, 1);
        if (option == 1) {
            grid = enterGrid();
        } else if (option == 2) {
            grid = chooseGridTemplates();
        } else {
            cout << "\nExiting the program...";
            break;
        }

        cout << "\nGrid state:\n";
        grid.show();

        cout << "\nChoose solving vatiant:\n1 - autosolve\n2 - solve yourself" << endl;
        while (true) {
            cout << "Select option: ";
            cin >> option;
            cin.ignore();

            if (option == 1) {
                cout << "\n--= Wait... Solving in prosses... =--" << endl;
                if (solveCave(&grid)) {
                   cout << "\nSolved Grid:\n";
                    grid.show();
                } else {
                    cout << "\nNo solution found!\n";
                }
                break;
            } else if (option == 2) {
                if (solveCaveUser(&grid)) {
                   cout << "\nSolved Grid:\n";
                    grid.show();
                }
                break;
            } else {
                cout << "Chose correct option!" << endl;
            }
        }

        cout << "\n" << endl;
    }
}
