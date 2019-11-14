#pragma once
#include <iostream>
#include "Point.h"


class Plane //Класс плоскости 
{
public:
	Plane();
	Plane(Point M0, Point M1, Point M2);//Конструктор плоскости через три точки
	double* getEquation();//Получить указатель на массив с уравнением плоксости
	double* getNormal();//Получить указатель на массив c нормалью плоскости
	void setEquation(Point M0, Point M1, Point M2);//Установить уравнение плоскости через три точки
	void setEquation(double a, double b, double c, double d);//Установить уравнение плоскости через коэффициенты уравнения 
private:
	double planeEquation_[4];//Коэффициенты уравнения плоскости Ax + By + Cz + D = 0
	double planeNormal_[3];//Вектор нормали к плоскости A, B, C
	void setNormal(double a, double b, double c);//Установить нормаль
	bool checkCollinearity(Point M0, Point M1, Point M2);//Проверка коллинеарности - лежат ли три точки на одной прямой
};
