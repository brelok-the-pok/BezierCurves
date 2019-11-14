#pragma once
#include <iostream>
#include "Point.h"


class Plane //����� ��������� 
{
public:
	Plane();
	Plane(Point M0, Point M1, Point M2);//����������� ��������� ����� ��� �����
	double* getEquation();//�������� ��������� �� ������ � ���������� ���������
	double* getNormal();//�������� ��������� �� ������ c �������� ���������
	void setEquation(Point M0, Point M1, Point M2);//���������� ��������� ��������� ����� ��� �����
	void setEquation(double a, double b, double c, double d);//���������� ��������� ��������� ����� ������������ ��������� 
private:
	double planeEquation_[4];//������������ ��������� ��������� Ax + By + Cz + D = 0
	double planeNormal_[3];//������ ������� � ��������� A, B, C
	void setNormal(double a, double b, double c);//���������� �������
	bool checkCollinearity(Point M0, Point M1, Point M2);//�������� �������������� - ����� �� ��� ����� �� ����� ������
};
