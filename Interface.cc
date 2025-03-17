#include "Interface.h"
#include <string.h>
#include <stdlib.h>

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

        char *num = strtok(line, " ");
        for (int j = 0; j < height && num != nullptr; j++) {
            grid.setPoint(i, j, Point(atoi(num)));
            num = strtok(nullptr, " ");
        }
    }
    cout << "\nGrid state:\n";
    grid.show();
}