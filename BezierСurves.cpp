// BezierСurves.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <cmath>
#include <cstring>
#include <stack>
#include <fstream>
#include <direct.h>
#include "Plane.h"
#include "Point.h"

void calculateCurve(Point* referencePoints, int rank, Point* curvePoints);//Рассчёт точек кривой Безье по заданным опорным точкам
bool readInputData(const char* fileName, Point* planePoints, std::stack<Point>* referencePointsStack);//Чтение из файла входных данных для постройки кривой Безье
bool writeOutputData(const char* fileName, Point* curvePoints);//Запись в файл спроецированных точек кривой Безье
int factorial(int val);//Факториал числа (Не рекурсивный)

int main()
{
	char currDir[100];
	_getcwd(currDir, 100);//Взятие текущей директории
	char inputDir[100];
	char outputDir[100];
	strcpy_s(inputDir, currDir);//Копирование текущей директории 
	strcpy_s(outputDir, currDir);
	strcat_s(inputDir, "\\inputData.txt");//Добавление к текущей директории имени файла
	strcat_s(outputDir, "\\outputData.txt");

	Point planePoints[3];
	std::stack<Point> referencePointsStack;

	if (!readInputData(inputDir, planePoints, &referencePointsStack)) {//Если не удалось открыть файл со входными данными
		std::cout << "File cannot be opened. Curve cannot be built" << std::endl << "Press any key to continue . . . " << std::endl;
		std::cin.get();
		return -1;
	}

	Plane plane(planePoints[0], planePoints[1], planePoints[2]);//Создание объекта плоскости по трём точкам
	int curveRank = referencePointsStack.size() - 1;//Степень кривой Безье
	Point* referencePoints = new Point[curveRank + 1];//Массив опорных точек кривой безье
	for (int i = curveRank; i >= 0; i--) {//Достаю из стека в опорные точки и записываю в обратном порядке в массив
		referencePoints[i] = referencePointsStack.top();
		referencePointsStack.pop();
	}
	Point* curvePoints = new Point[100000];//Выделение памяти под массив спроецированных точек кривой Безье
	
	calculateCurve(referencePoints, curveRank, curvePoints);
	
	for (int i = 0; i < 100000; i++)
	{
		curvePoints[i].projectOnPlane(plane);//Проецирование точки на плоксость 
	}
	
	if (!writeOutputData(outputDir, curvePoints)) //Неудалось открыть файл 
		std::cout << "Error in curve data writing" << std::endl;
	else 
		std::cout << "The curve is built successfully" << std::endl;
	
	std::cout << "Press any key to continue . . . " << std::endl;
	delete[] referencePoints;//Высвобождение памяти
	std::cin.get();
}

void calculateCurve(Point* referencePoints, int rank, Point* curvePoints) {//Рассчёт точек кривой Безье по заданным опорным точкам
	std::stack<Point> pointStack;
	Point currentCurvePoint;
	do {
		for (double t = 0.0; t <= 1.0; t += 1.e-5) {
			for (int i = 0; i < rank + 1; i++) {
				currentCurvePoint.setPoint(0, 0, 0);
				double multiplier = factorial(rank);//Рассчёт вклада в значение текущей точки
				multiplier *= pow(t, i);
				multiplier *= pow(1 - t, rank - 1);
				multiplier /= factorial(i);
				multiplier /= factorial(rank - i);

				double x = referencePoints[i].x * multiplier;
				double y = referencePoints[i].y * multiplier;
				double z = referencePoints[i].z * multiplier;
				Point curvePart(x, y, z);
				currentCurvePoint += curvePart;
			}
			pointStack.push(currentCurvePoint);//Сохранение текущей точки в стек
		}
	} while (referencePoints[rank - 1] != currentCurvePoint);

	for (int i = 100000 - 1; i >= 0; i--) {
		curvePoints[i] = pointStack.top();
		pointStack.pop();
	}
	
}

bool readInputData(const char* fileName, Point* planePoints, std::stack<Point> *referencePointsStack) {//Чтение из файла входных данных для постройки кривой Безье
	char readBuffer[50];

	std::ifstream fin(fileName, std::ios_base::in);//Создание потока на чтение
	if (!fin.is_open()) {//Проверка открытия потока
		return false;//Чтение не удалось
	}

	char* pointBuff;
	char* nextToken = nullptr;
	double coordinats[3];

	//Чтение точек образующий плоскость
	for (int k = 0; k < 3; k++) {
		fin.getline(readBuffer, 50);//Чтение строки из потока
		pointBuff = strtok_s(readBuffer, ";", &nextToken);//Разбиение полученной строки на массив элементов разделённых знаком ';'

		for (int i = 0; i < 3; i++)
		{
			coordinats[i] = atof(pointBuff);//Преобразование строки в тип double
			pointBuff = strtok_s(nullptr, ";", &nextToken);
		}

		planePoints[k].setPoint(coordinats[0], coordinats[1], coordinats[2]);//Инициализация k-ой точки координатами
	}

	//Чтение опорных точек
	while (fin.getline(readBuffer, 50)) {//Пока не конец файла
		pointBuff = strtok_s(readBuffer, ";", &nextToken);

		for (int i = 0; i < 3; i++)
		{
			coordinats[i] = atof(pointBuff);
			pointBuff = strtok_s(nullptr, ";", &nextToken);
		}

		Point currPoint(coordinats[0], coordinats[1], coordinats[2]);
		referencePointsStack->push(currPoint);//Сохранение опорной точки в стэк
	}

	fin.close();//Закрытие потока чтения
	return true;//Чтение прошло удачно
}

bool writeOutputData(const char* fileName, Point* curvePoints) {//Запись в файл спроецированных точек кривой Безье
	std::ofstream fout(fileName);//Создание потока
	if (!fout.is_open()) {//Проверка открытия потока
		std::cout << "File cannot be opened";
		return false;//К сожалению, запись не удалась
	}

	for (int i = 0; i < 100000; i++) //Форматированный вывод в поток координат точки
		fout << curvePoints[i].x << ';' << curvePoints[i].y << ';' << curvePoints[i].z << std::endl;

	fout.close();//Закрытие потока
	return true;//Запись удалась
}

int factorial(int val) {//Факториал числа (Не рекурсивный)
	int result = 1;

	for (int i = 1; i < val + 1; i++) {
		result *= i;
	}
	return result;
}



