#include "Point.h"
#include "Plane.h"
Point::Point() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::projectOnPlane(Plane plane) {
	double x = this->x;
	double y = this->y;
	double z = this->z;

	double* equation = plane.getEquation();

	double param = equation[0] * x + equation[1] * y + equation[2] * z + equation[3];
	param /= pow(equation[0], 2) + pow(equation[1], 2) + pow(equation[2], 2);
	x += equation[0] * param;
	y += equation[1] * param;
	z += equation[2] * param;

	this->x = x;
	this->y = y;
	this->z = z;

	delete[] equation;
}

void Point::setPoint(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Point::operator!=(Point& other) {
	if (this->x != other.x || this->y != other.y || this->z != other.z)
		return false;
	else
		return true;
}

Point& Point::operator+=(Point& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Point& Point::operator=(Point& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}