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

//Функція яка буде визиватися в мейні (Запуск)
void init(){
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
    cout << "\nGrid state:\n";
    grid.show();

    cout << "\n--= Wait... Solving in prosses... =--" << endl;
    if (solveCave(&grid)) {
        cout << "\nSolved Grid:\n";
        grid.show();
    } else {
        cout << "\nNo solution found!\n";
    }
}

