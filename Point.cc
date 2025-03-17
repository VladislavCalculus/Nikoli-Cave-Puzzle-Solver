#include "Point.h"
#include <cstring>

//Конструктор без параметрів - створює пусту клітинку.
Point::Point(){
	value = 0;
	type = CELL;
	str = new char[3];
	strcpy(str, " . ");
}

//Конструктор з параметром - створює клітинку з числом.
Point::Point(int number){
	if (number < 0) {
		exit(1);
	}
	value = number;
	type = VALUED_CELL;
	str = intToChar(number);
}
//P.S. для себе. Гарною пракикою при створенні хоча б одного з нижче зроблених 3-х функцій є робити всі одразу. НА вікіпедії це зветься Rule of 3
//Деструкор класу точки для очищення str
Point::~Point(){
	delete[] str;
}

// Конструктор копіювання
Point::Point(const Point& other) {
    value = other.value;
    type = other.type;
    if (other.str) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    } else {
        str = nullptr;
    }
}

// Оператор присвоєння
Point& Point::operator=(const Point& other) {
    if (this == &other) return *this; // захист від самоприсвоєння

    value = other.value;
    type = other.type;

    delete[] str;
    if (other.str) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    } else {
        str = nullptr;
    }

    return *this;
}

//Перетворює точку на стіну.
void Point::wallify(){
	if (value > 0) {
		return;
	}
	value = -1;
	type = WALL;
	strcpy(str, " # ");
}

//Перетворює точку на пусту клітинку.
void Point::cellify(){
	if (value > 0) {
		return;
	}
	value = 0;
	type = CELL;
	strcpy(str, " . ");
}
	
//Для отримання числа як рядка
char* Point::intToChar(int value) {
    char *str = new char[4];
    sprintf(str, " %d ", value);
    return str;
}

