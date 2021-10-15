#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

double leftRectanglesMethodNoVector(double a, double b, double h)
{
	double area = h * (8 / (1 + a * a));
#pragma loop(no_vector)
	while (a < b)
	{
		area = area + h * (8 / (1 + a * a));
		a = a + h;
	}

	return area;
}

double rightRectanglesMethodNoVector(double a, double b, double h)
{
	double area = h * (8 / (1 + b * b));
#pragma loop(no_vector)
	while (b > a)
	{
		area = area + h * (8 / (1 + b * b));
		b = b - h;
	}

	return area;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	// Границы интегрирования.
	double a = 0;
	double b = 1;

	cout << "Запускаем последовательную программу с отключённой векторизацией." << endl;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	double n = 100;
	double h = (b - a) / n;

	cout << "Метод левых прямоугольников:" << endl;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationLeftRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 1000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 10000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 100000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 1000000;
	h = (b - a) / n;
	cout << leftRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationLeftRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом левых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationLeftRectanglesNoVector.count() << " секунд." << endl << endl;


	t1 = chrono::high_resolution_clock::now();

	cout << "Метод правых прямоугольников с отключённой векторизацией:" << endl;
	n = 100;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	chrono::duration <double> durationRightRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом правых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 1000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом правых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 10000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом правых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 100000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом правых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;


	n = 1000000;
	h = (b - a) / n;
	cout << rightRectanglesMethodNoVector(a, b, h) << endl;
	t2 = chrono::high_resolution_clock::now();
	durationRightRectanglesNoVector = (t2 - t1);
	cout << "Время подсчёта методом правых прямоугольников с отключённой векторизацией с шагом " << n << ": " << durationRightRectanglesNoVector.count() << " секунд." << endl << endl;

	return 0;
}