#pragma once
class Plane;

class Point //Класс точки с тремя координатами
{
public:
	double x, y, z;//Координаты точки
	Point();
	Point(double x, double y, double z);//Конструктор точки через значения её координат
	void projectOnPlane(Plane plane);//Проецирование точки на заданную плокость
	void setPoint(double x, double y, double z);//Установки координат точки
	bool operator!=(Point& other);
	Point& operator+=(Point& other);
	Point& operator=(Point& other);
};
