#include "Plane.h"
#include "Point.h"

Plane::Plane() {
	setEquation(0, 0, 0, 0);
}
Plane::Plane(Point M0, Point M1, Point M2) {
	setEquation(M0, M1, M2);
}

double* Plane::getEquation() {
	double* equationCopy = new double[4];
	equationCopy[0] = this->planeEquation_[0];
	equationCopy[1] = this->planeEquation_[1];
	equationCopy[2] = this->planeEquation_[2];
	equationCopy[3] = this->planeEquation_[3];
	return equationCopy;
}

double* Plane::getNormal() {
	double* normalCopy = new double[3];
	normalCopy[0] = this->planeNormal_[0];
	normalCopy[1] = this->planeNormal_[1];
	normalCopy[2] = this->planeNormal_[2];
	return normalCopy;
}

void Plane::setEquation(Point M0, Point M1, Point M2) {
	if (checkCollinearity(M0, M1, M2)) {
		throw std::exception(std::invalid_argument("Plane cannot be built. Points are on the same line"));
	}
	double a = (M1.y - M0.y) * (M2.z - M0.z) - (M2.y - M0.y) * (M1.z - M0.z);
	double b = (M1.x - M0.x) * (M2.z - M0.z) - (M2.x - M0.x) * (M1.z - M0.z);
	b *= -1;
	double c = (M1.x - M0.x) * (M2.y - M0.y) - (M2.x - M0.x) * (M1.y - M0.y);
	double d = -a * M0.x - b * M0.y - c * M0.z;

	setEquation(a, b, c, d);
}

void Plane::setEquation(double a, double b, double c, double d) {
	planeEquation_[0] = a;
	planeEquation_[1] = b;
	planeEquation_[2] = c;
	planeEquation_[3] = d;
	setNormal(a, b, c);
}

void Plane::setNormal(double a, double b, double c) {
	planeNormal_[0] = a;
	planeNormal_[1] = b;
	planeNormal_[2] = c;
}
bool Plane::checkCollinearity(Point M0, Point M1, Point M2) {
	double vect1[3] = { M1.x - M0.x, M1.y - M0.y , M1.z - M0.z };//Нахождение координат векторов
	double vect2[3] = { M2.x - M0.x, M2.y - M0.y , M2.z - M0.z };
	double eps = 1.e-5;
	double n = 1;
	if (vect2[0] != 0) {//Нахождение ненулевого элемента второго вектора
		n = vect1[0] / vect2[0];
	}
	else if (vect2[1] != 0) {
		n = vect1[1] / vect2[1];
	}
	else {
		n = vect1[2] / vect2[2];
	}

	double condition1 = abs(vect2[0] * n - vect1[0]);
	double condition2 = abs(vect2[1] * n - vect1[1]);
	double condition3 = abs(vect2[2] * n - vect1[2]);

	if (condition1 + condition2 + condition3 >= 3 * eps) //Векторы не коллинеарны
		return false;
	else 
		return true;//Векторы коллинеарны
}