#pragma once
class Plane;

class Point //����� ����� � ����� ������������
{
public:
	double x, y, z;//���������� �����
	Point();
	Point(double x, double y, double z);//����������� ����� ����� �������� � ���������
	void projectOnPlane(Plane plane);//������������� ����� �� �������� ��������
	void setPoint(double x, double y, double z);//��������� ��������� �����
	bool operator!=(Point& other);
	Point& operator+=(Point& other);
	Point& operator=(Point& other);
};
