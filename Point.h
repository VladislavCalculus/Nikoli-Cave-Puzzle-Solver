#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

//Перелік типів точок.
enum PointType {
	CELL, VALUED_CELL, WALL
};

//Клас точки на полі. Має мінімальний набір методів для зручності.
struct Point{
	int value;
	PointType type;
	char *str; //Змінна з текстом для візуалізації таблиці

	Point();
	Point(int number);
	~Point();
	Point(const Point& other);
	Point& operator =(const Point& other);


	void wallify();
	void cellify();
	
private:
	char *intToChar(int value);
};

#endif